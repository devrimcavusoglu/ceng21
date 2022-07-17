#include "image.hpp"


namespace fs = std::filesystem;

// Public members

Fat32Image::Fat32Image(char *path) {
	this->image_file = path;
	int fd = open(this->image_file.c_str(), O_RDONLY);
	read(fd, &this->BPB, sizeof(this->BPB));

	this->fat_entry_offset = BPB.ReservedSectorCount * BPB.BytesPerSector;
	this->bytes_per_cluster = BPB.BytesPerSector * BPB.SectorsPerCluster;
	this->data_area_start = this->sector2byte(BPB.ReservedSectorCount + BPB.NumFATs * BPB.extended.FATSize);

	this->root.path = "/"; 
	this->root.cluster = BPB.extended.RootCluster;
	this->root.is_dir = true;
	this->root.exists = true;
	this->cwd = this->root; // set CWD as root

	uint32_t table_size = sector2byte(BPB.extended.FATSize)/4;
	uint32_t fat_table_temp[table_size];
	read_fat_table(fd, fat_entry_offset, fat_entry_offset + sector2byte(BPB.extended.FATSize), fat_table_temp);
	this->fat_table.insert(this->fat_table.begin(), fat_table_temp, fat_table_temp+table_size);
	close(fd);
}


fs::path Fat32Image::get_cwd() {
	return this->cwd.path;
}


void Fat32Image::change_directory(fs::path path) {
	path_t p = this->locate(path);

	if (!p.exists or !p.is_dir) // Sanity check
		return;
	this->cwd = p;
}


void Fat32Image::list_directory(fs::path path, bool verbose) {
	path_t p = this->locate(path);
	if (!p.exists or !p.is_dir)	// Sanity check
		return;

	std::vector<FatFileEntry> dirents;
	while (true) {
		dirents = this->get_dir_entries(p.cluster);

		for (size_t i = 0; i < dirents.size(); i++) {
			if (dirents[i].state != 1 or dirents[i].is_dir > 1)	// filter out erased or dot entries
				continue;
			if (!verbose) {
				printf("%s ", u16bytestostr(dirents[i].name).c_str());
			}
			else {
				printf("%s % 9u %s %s\n",
					dirents[i].file_desc,
					dirents[i].msdos.fileSize,
				 	&(dirents[i].datetime_str[1]), // no idea, but buffer mysteriously puts null term. as first char, this is a work-around fix. (#L143)
					u16bytestostr(dirents[i].name).c_str()
				);
			}
		}

		if (!verbose)
			puts("");

		if (this->fat_table[p.cluster] == FAT_ENTRY_EOC or this->fat_table[p.cluster] == FAT_ENTRY_BAD)
			break;
		else
			p.cluster = this->fat_table[p.cluster];
	}
}


void Fat32Image::cat_file(fs::path path) {
	path_t p = this->locate(path);
	if (!p.exists or p.is_dir)	// Sanity check
		return;

	while (p.cluster != FAT_ENTRY_EOC and p.cluster != FAT_ENTRY_BAD) {
		std::cout << get_cluster(p.cluster);
		p.cluster = this->fat_table[p.cluster];
	}
}


void Fat32Image::make_directory(fs::path path, FatFileEntry *moved_entry) {
	path_t p = this->locate(path);
	if (p.exists)
		return;
	this->make_entry(path, true, moved_entry);
}


void Fat32Image::touch(fs::path path, FatFileEntry *moved_entry) {
	path_t p = this->locate(path);
	if (p.exists)
		return;
	this->make_entry(path, false, moved_entry);
}


void Fat32Image::move(fs::path src, fs::path dest) {
	path_t p_src = this->locate(src);
	path_t p_dest = this->locate(dest);
	fs::path dest_src = dest / src.filename(); 
	path_t p_dest_src = this->locate(dest_src);
	
	// Sanity check
	if (!p_src.exists)
		return;
	if (!p_dest.exists or !p_dest.is_dir)
		return;
	if (p_dest_src.exists)
		return;

	FatFileEntry src_entry;
	// mark src as deleted and copy entry to be deleted to src_entry
	this->mark_deleted(p_src.pclusters.back(), p_src.path.filename(), src_entry);

	// make entry on dest
	if (p_src.is_dir)
		make_directory(dest_src, &src_entry);
	else
		touch(dest_src, &src_entry);
}


// Private members

path_t Fat32Image::locate(fs::path path) {
	std::vector<std::string> spath = tokenizeStringPath(path);
	path_t current_path = this->cwd;

	if (spath.front() == ".") {
		spath.erase(spath.begin());
	}
	else if (spath.front() == ".." and !current_path.pclusters.empty()) {
		current_path.path = current_path.path.parent_path();
		current_path.cluster = current_path.pclusters.back();
		current_path.pclusters.pop_back();
		spath.erase(spath.begin());
	}
	else if (spath.front() == "") { // absolute path
		current_path = this->root;
		spath.erase(spath.begin());
	}

	if (spath.empty())
		return current_path;

	size_t i = 0; // spath index
	std::vector<FatFileEntry> dirents;
	while (true) {
		dirents = this->get_dir_entries(current_path.cluster);
		current_path.exists = false;
		for (size_t j = 0; j < dirents.size(); j++) {
			if (u16bytestostr(dirents[j].name) != spath[i]) // not found
				continue; 
			current_path.exists = true;
			current_path.path /= spath[i];
			current_path.pclusters.push_back(current_path.cluster);
			current_path.cluster = (dirents[j].msdos.eaIndex << 16) | dirents[j].msdos.firstCluster;
			current_path.is_dir = dirents[j].is_dir;
			if (i++ == spath.size() - 1) { // last entry
				return current_path;
			}
			break; // no need to traverse further, found!
		}

		if (!current_path.exists) {
			if (this->fat_table[current_path.cluster] == FAT_ENTRY_EOC or this->fat_table[current_path.cluster] == FAT_ENTRY_BAD)
				break;
			current_path.cluster = this->fat_table[current_path.cluster];
		}
	}

	return current_path;  // iff path not exists
}


int Fat32Image::cluster_has_space(unsigned int cluster_id) {
	std::vector<FatFileEntry> dirents = this->get_dir_entries(cluster_id);
	if (this->bytes_per_cluster - dirents.size()*64 >= 64)
		return dirents.size()*64;
	return -1;
}


void Fat32Image::make_entry(fs::path path, bool is_dir, FatFileEntry *moved_entry) {
	std::string filename = path.filename();
	if (path.has_parent_path())
		path = path.parent_path();
	else
		path = this->cwd.path;

	path_t p = this->locate(path);
	if (!p.exists or !p.is_dir)  // Sanity check
		return;

	off_t cur_offset;
	uint32_t cluster_id = p.cluster;
	int free_entry_offset;
	bool allocate_new = false;
	while (true) {
		free_entry_offset = this->cluster_has_space(cluster_id);
		if (free_entry_offset == -1) {
			if (this->fat_table[cluster_id] == FAT_ENTRY_EOC) {
				allocate_new = true;
				break;
			}
			cluster_id = this->fat_table[cluster_id];
			continue;
		}
		cur_offset = cluster2byte(cluster_id) + free_entry_offset;
		break;
	}

	// If cluster capacity is full, allocate a new cluster
	if (allocate_new) {	
		uint32_t free_cluster_id = this->next_free_cluster();
		this->update_fat_table(cluster_id, free_cluster_id);
		this->update_fat_table(free_cluster_id, FAT_ENTRY_EOC);
		cur_offset = cluster2byte(free_cluster_id);
	}

	FatFileEntry fat_entry;
	if (moved_entry) {
		fat_entry = *moved_entry;

		// only update last access time
		std::tm *now = get_time();
		fat_entry.msdos.lastAccessTime = uformattime(now, true);
	}
	else {

		// filname -> increment (unique ids) 
		// Filename contains only digits (ASCII) in real FAT32, e.g after 0x39, the 
		// next id is 0x31 0x30 for ASCII "~10", but current (current is 0x3a)
		// solution assures uniqueness, so I will not change for now, but I'll if I have time.
		// fat_entry.msdos.filename[0] = FAT_DIRENT_TILDE;
		// fat_entry.msdos.filename[1] = FAT_DIRENT_SHORTNAME_START + (free_entry_offset/64);
		// for (int i = 2; i<sizeof(fat_entry.msdos.filename); i++)
		// 	fat_entry.msdos.filename[i] = FAT_DIRENT_SHORTNAME_PAD;


		fix_filename_digits(fat_entry.msdos.filename, free_entry_offset);
		fat_entry.lfn.sequence_number = 0x41;
		strtou16bytes(filename, fat_entry.lfn.name1, 5);
		fat_entry.lfn.attributes = 0x0f;
		fat_entry.lfn.reserved = 0x00;
		fat_entry.lfn.checksum = cksum((unsigned char*)fat_entry.msdos.filename);
		if (filename.size() > 5)
			strtou16bytes(filename.substr(5), fat_entry.lfn.name2, 6);
		fat_entry.lfn.firstCluster = 0x0000;
		if (filename.size() > 11)
			strtou16bytes(filename.substr(11), fat_entry.lfn.name3, 2);


		// extension pad only
		for (int i = 2; i<sizeof(fat_entry.msdos.extension); i++)
			fat_entry.msdos.extension[i] = FAT_DIRENT_SHORTNAME_PAD;

		if (is_dir)
			fat_entry.msdos.attributes = 0x10;
		else
			fat_entry.msdos.attributes = 0x20;
		fat_entry.msdos.reserved = 0;

		fat_entry.msdos.creationTimeMs = 0; // no ms precision for now

		std::tm *now = get_time();
		fat_entry.msdos.creationTime = uformattime(now, true);
		fat_entry.msdos.creationDate = uformattime(now);

		fat_entry.msdos.lastAccessTime = fat_entry.msdos.creationTime;

		fat_entry.msdos.modifiedTime = fat_entry.msdos.creationTime;
		fat_entry.msdos.modifiedDate = fat_entry.msdos.creationDate;

		uint32_t entry_id = this->next_free_cluster();
		fat_entry.msdos.eaIndex = (entry_id & FAT_DIRENT_EAINDEX_MASK) >> 16;
		fat_entry.msdos.firstCluster = entry_id & FAT_DIRENT_FIRSTCLUSTER_MASK;

		fat_entry.msdos.fileSize = 0;

		// update the FAT table on memory & disk
		this->update_fat_table(entry_id, FAT_ENTRY_EOC);

		if (is_dir) {
			FatFileEntry dot_entry;	// curent dir
			FatFileEntry dotdot_entry;	// parent dir

			fill_dot_entry(dot_entry);
			fill_dot_entry(dotdot_entry);

			dotdot_entry.msdos.filename[1] = FAT_DIRENT_DOT;

			dot_entry.msdos.creationTime = fat_entry.msdos.creationTime;
			dot_entry.msdos.creationDate = fat_entry.msdos.creationDate;
			dot_entry.msdos.lastAccessTime = fat_entry.msdos.creationDate;
			dot_entry.msdos.modifiedTime = fat_entry.msdos.creationTime;
			dot_entry.msdos.modifiedDate = fat_entry.msdos.creationDate;
			dot_entry.msdos.eaIndex = fat_entry.msdos.eaIndex;
			dot_entry.msdos.firstCluster = fat_entry.msdos.firstCluster;


			dotdot_entry.msdos.creationTime = fat_entry.msdos.creationTime;
			dotdot_entry.msdos.creationDate = fat_entry.msdos.creationDate;
			dotdot_entry.msdos.lastAccessTime = fat_entry.msdos.creationDate;
			dotdot_entry.msdos.modifiedTime = fat_entry.msdos.creationTime;
			dotdot_entry.msdos.modifiedDate = fat_entry.msdos.creationDate;
			dotdot_entry.msdos.eaIndex = (p.cluster & FAT_DIRENT_EAINDEX_MASK) >> 16;
			dotdot_entry.msdos.firstCluster = p.cluster & FAT_DIRENT_FIRSTCLUSTER_MASK;

			write_fat_entry(cluster2byte(entry_id), dot_entry, true);
			write_fat_entry(cluster2byte(entry_id) + 32, dotdot_entry, true);
		}
	}

	printf("Current offset -> 0x%x | Cluster -> %u\n", cur_offset, cluster_id);

	// Write the entry on cluster
	write_fat_entry(cur_offset, fat_entry);
}


void Fat32Image::mark_deleted(unsigned int cluster_id, std::string name, FatFileEntry &fat_entry) {
	std::vector<FatFileEntry> dirents = this->get_dir_entries(cluster_id);
	off_t cur_offset = cluster2byte(cluster_id);
	for (size_t j = 0; j < dirents.size(); j++) {
		if (u16bytestostr(dirents[j].name) != name) { // not found
			cur_offset += 64; // lfn + msdos
			continue; 
		}
		fat_entry = dirents[j];
		dirents[j].msdos.filename[0] = FAT_DIRENT_DELETED;
		this->write_fat_entry(cur_offset, dirents[j]);
		break;
	}
}


std::vector<FatFileEntry> Fat32Image::get_dir_entries(int cluster_id) {
	std::vector<FatFileEntry> entries;
	if (cluster_id < 2)
		return entries;
	int fd = open(this->image_file.c_str(), O_RDONLY);
	off_t cur_offset = this->cluster2byte(cluster_id);
	bool stop = false;
	FatFileEntry fat_entry;
	while (true) {
		fat_entry = read_dir_entry(fd, cur_offset);
		cur_offset = lseek(fd, 0, SEEK_CUR);
		// stop if hit free/unused or hit cluster size
		if (fat_entry.state == 0 or cur_offset - cluster2byte(cluster_id) > this->bytes_per_cluster)
			break;
		entries.emplace_back(fat_entry);
	}
	close(fd);

	return entries;
}


void Fat32Image::write_fat_entry(int offset, FatFileEntry fat_entry, bool msdos_only) {
	std::ofstream out_s(this->image_file, std::ios_base::binary | std::ios_base::out | std::ios_base::in);
	out_s.seekp(offset, std::ios_base::beg);


	if (!msdos_only) {
		// lfn 
		out_s.write((char*)&fat_entry.lfn.sequence_number, 1);
		out_s.write((char*)fat_entry.lfn.name1, 10);
		out_s.write((char*)&fat_entry.lfn.attributes, 1);
		out_s.write((char*)&fat_entry.lfn.reserved, 1);
		out_s.write((char*)&fat_entry.lfn.checksum, 1);
		out_s.write((char*)fat_entry.lfn.name2, 12);
		out_s.write((char*)&fat_entry.lfn.firstCluster, 2);
		out_s.write((char*)fat_entry.lfn.name3, 4);
	}

	// msdos
	out_s.write((char*)fat_entry.msdos.filename, 8);
	out_s.write((char*)fat_entry.msdos.extension, 3);
	out_s.write((char*)&fat_entry.msdos.attributes, 1);
	out_s.write((char*)&fat_entry.msdos.reserved, 1);
	out_s.write((char*)&fat_entry.msdos.creationTimeMs, 1);
	out_s.write((char*)&fat_entry.msdos.creationTime, 2);
	out_s.write((char*)&fat_entry.msdos.creationDate, 2);
	out_s.write((char*)&fat_entry.msdos.lastAccessTime, 2);
	out_s.write((char*)&fat_entry.msdos.eaIndex, 2);
	out_s.write((char*)&fat_entry.msdos.modifiedTime, 2);
	out_s.write((char*)&fat_entry.msdos.modifiedDate, 2);
	out_s.write((char*)&fat_entry.msdos.firstCluster, 2);
	out_s.write((char*)&fat_entry.msdos.fileSize, 4);

	out_s.close();
}


void Fat32Image::update_fat_table(uint32_t entry_id, uint32_t value) {
	// Update on memory
	this->fat_table[entry_id] = value;

	// Update on disk
	std::ofstream out_s(this->image_file, std::ios_base::binary | std::ios_base::out | std::ios_base::in);
	
	uint32_t entry_offset = this->fat_entry_offset + entry_id * 4;
	out_s.seekp(entry_offset, std::ios_base::beg);

	out_s.write((char*)&value, 4);
}


std::string Fat32Image::get_cluster(int cluster_id) {
	char buffer[this->bytes_per_cluster];
	int fd = open(this->image_file.c_str(), O_RDONLY);
	read_data(fd, this->cluster2byte(cluster_id), buffer, this->bytes_per_cluster);
	close(fd);
	std::string content = buffer;
	content = content.substr(0, this->bytes_per_cluster);
	return content;
}

uint32_t Fat32Image::next_free_cluster() {
	for (uint32_t i = 2; i < this->fat_table.size(); i++) {
		if (this->fat_table[i] == 0)
			return i;
	}
}

unsigned int Fat32Image::cluster2byte(unsigned int cluster_id) {
	return this->data_area_start + (cluster_id - 2) * sector2byte(this->BPB.SectorsPerCluster);
}

unsigned int Fat32Image::sector2byte(unsigned int sector_id) {
	return sector_id * this->BPB.BytesPerSector;
}
