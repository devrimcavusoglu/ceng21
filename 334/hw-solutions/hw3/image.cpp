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

	uint32_t fat_table_temp[sector2byte(BPB.extended.FATSize)/4];
	read_fat_table(fd, fat_entry_offset, fat_entry_offset + sector2byte(BPB.extended.FATSize), fat_table_temp);
	this->fat_table = fat_table_temp;
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


void Fat32Image::touch(fs::path path) {
	std::string filename = path.filename();
	if (path.has_parent_path())
		path = path.parent_path();
	else
		path = "/";

	path_t p = this->locate(path);
	if (!p.exists or !p.is_dir)  // Sanity check
		return;

	uint32_t cluster_id = p.cluster;
	FatFileEntry fat_entry;
	std::vector<FatFileEntry> dirents = this->get_dir_entries(cluster_id);
	uint32_t cur_offset = cluster2byte(cluster_id) + dirents.size() * 64;
	while (true) {
		if (dirents.size()*64 > (this->bytes_per_cluster - 64)) {
			cluster_id = this->fat_table[cluster_id];
			if (cluster_id == FAT_ENTRY_EOC or cluster_id == FAT_ENTRY_BAD)
				return;
			dirents = this->get_dir_entries(cluster_id);
			cur_offset = cluster2byte(cluster_id) + dirents.size() * 64;
			continue;
		}
		break;		
	}
	
	fat_entry.lfn.sequence_number = 0x41;
	strtou16bytes(filename, fat_entry.lfn.name1, 5);
	fat_entry.lfn.attributes = 0x0f;
	fat_entry.lfn.reserved = 0x00;
	fat_entry.lfn.checksum = cksum((unsigned char*)filename.c_str());
	if (filename.size() > 5)
		strtou16bytes(filename.substr(5), fat_entry.lfn.name2, 6);
	fat_entry.lfn.firstCluster = 0x0000;
	if (filename.size() > 11)
		strtou16bytes(filename.substr(11), fat_entry.lfn.name3, 2);

	write_fat_entry(cur_offset, fat_entry);
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
		if (fat_entry.state == 0)	// free/unused
			break;
		entries.emplace_back(fat_entry);
	}
	close(fd);

	return entries;
}


void Fat32Image::write_fat_entry(int offset, FatFileEntry fat_entry) {
	std::ofstream s(this->image_file, std::ios_base::binary | std::ios_base::out | std::ios_base::in);
	s.seekp(offset, std::ios_base::beg);

	// char name1[10];
	// char name2[12];
	// char name3[4];


	// // lfn 
	// s.write((char*)&fat_entry.lfn, 32);	
	// // msdos
	// s.write((char*)&fat_entry.msdos, 32);
}


std::string Fat32Image::get_cluster(int cluster_id) {
	char buffer[this->bytes_per_cluster];
	int fd = open(this->image_file.c_str(), O_RDONLY);
	read_data(fd, this->cluster2byte(cluster_id), buffer, this->bytes_per_cluster);
	// (!) No null termination to allow string concatenation.
	close(fd);
	std::string content = buffer;
	return content;
}

uint32_t Fat32Image::next_free_cluster() {
	for (size_t i = 2; i < sizeof(this->fat_table); i++) {
		if (this->fat_table[i] == 0)
			return this->fat_table[i];
	}
}

int Fat32Image::cluster2byte(int cluster_id) {
	return this->data_area_start + (cluster_id - 2) * sector2byte(this->BPB.SectorsPerCluster);
}

int Fat32Image::sector2byte(int sector_id) {
	return sector_id * this->BPB.BytesPerSector;
}
