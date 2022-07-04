#include "image.hpp"
#include "util.hpp"


namespace fs = std::filesystem;

// Public members

Fat32Image::Fat32Image(char *path) {
	this->image_file = path;
	int fd = open(this->image_file.c_str(), O_RDONLY);
	read_bpb(fd, this->BPB);

	this->fat_entry_offset = BPB.ReservedSectorCount * BPB.BytesPerSector;
	this->bytes_per_cluster = BPB.BytesPerSector * BPB.SectorsPerCluster;
	this->data_area_start = this->sector2byte(BPB.ReservedSectorCount + BPB.NumFATs * BPB.extended.FATSize);

	this->root.path = "/"; 
	this->root.cluster = BPB.extended.RootCluster;
	this->root.is_dir = true;
	this->root.exists = true;
	this->cwd = this->root; // set CWD as root

	printf(
		"BPB Information:\n"
		"	BS_JumpBoot: %p\n"
		"	BS_OEMName: %s\n"
		"	BPS: %d\n"
		"	SPC: %d\n"
		"	ReservedSectorCount: %d\n"
		"	NumFATs: %d\n"
		"	RootEntryCount: %d (should be 0)\n"
		"	TotalSectors16: %d (should be 0)\n"
		"	Media: %p\n"
		"	FATSize16: %d (should be 0)\n"
		"	SectorsPerTrack: %d\n"
		"	NumberOfHeads: %d\n"
		"	HiddenSectors: %d\n"
		"	TotalSectors32: %d\n",
		BPB.BS_JumpBoot,
		BPB.BS_OEMName,
		BPB.BytesPerSector,
		BPB.SectorsPerCluster,
		BPB.ReservedSectorCount,
		BPB.NumFATs,
		BPB.RootEntryCount,
		BPB.TotalSectors16,
		BPB.Media,
		BPB.FATSize16,
		BPB.SectorsPerTrack,
		BPB.NumberOfHeads,
		BPB.HiddenSectors,
		BPB.TotalSectors32
	);
	printf(
		"=====================Extended Params=====================\n"
		"	FATSize: %d\n"
		"	ExtFlags: %d\n"
		"	FSVersion: %d\n"
		"	RootCluster: %d\n"
		"	FSInfo: %d\n"
		"	BkBootSec: %d\n"
		"	BS_DriveNumber: %d\n"
		"	BS_Reserved1: %d\n"
		"	BS_BootSig: %d\n"
		"	BS_VolumeID: %u\n"
		"	BS_VolumeLabel: %s\n"
		"	BS_FileSystemType: %s\n"
		"========================================================\n",
		BPB.extended.FATSize,
		BPB.extended.ExtFlags,
		BPB.extended.FSVersion,
		BPB.extended.RootCluster,
		BPB.extended.FSInfo,
		BPB.extended.BkBootSec,
		BPB.extended.BS_DriveNumber,
		BPB.extended.BS_Reserved1,
		BPB.extended.BS_BootSig,
		BPB.extended.BS_VolumeID,
		BPB.extended.BS_VolumeLabel,
		BPB.extended.BS_FileSystemType
	);
	printf("fat entry offset: %d\n", this->fat_entry_offset);
	printf("data area offset: %d\n", this->data_area_start);
	printf("bytes per cluster: %d\n", this->bytes_per_cluster);
	uint32_t fat_table_temp[sector2byte(BPB.extended.FATSize)/4];
	read_fat_table(fd, fat_entry_offset, fat_entry_offset + sector2byte(BPB.extended.FATSize), fat_table_temp);
	this->fat_table = fat_table_temp;
	close(fd);
}


fs::path Fat32Image::get_cwd() {
	return this->cwd.path;
}


void Fat32Image::change_directory(fs::path path) {
	std::cout << "path: " << path << std::endl;
	path_t p = this->locate(path);
	printf(
		"path: %s\n"
		"cluster: %d\n"
		"parent cluster: %d\n"
		"is_dir: %d\n"
		"exists: %d\n",
		p.path.c_str(),
		p.cluster,
		(p.pclusters.empty() ? -1 : p.pclusters.back()),
		p.is_dir,
		p.exists
	);
	if (!p.exists or !p.is_dir)
		return;
	this->cwd = p;
}

// Private members

path_t Fat32Image::locate(fs::path path) {
	// ** incorrectly locates path -> folder2/folder2/folder3
	std::vector<std::string> spath = tokenizeStringPath(path);
	path_t current_path = this->cwd;
	if (!current_path.is_dir) {
		current_path.path = current_path.path.parent_path();
		current_path.cluster = current_path.pclusters.back();
		current_path.pclusters.pop_back();
		current_path.is_dir = true;
	}

	if (spath.front() == ".." and !current_path.pclusters.empty()) {
		current_path.path = current_path.path.parent_path();
		current_path.cluster = current_path.pclusters.back();
		current_path.pclusters.pop_back();
		spath.erase(spath.begin());
	}
	else if (spath.front() == "") { // absolute path
		current_path = this->root;
		if (spath.size() == 1) 
			return current_path;
		spath.erase(spath.begin());
	}

	int i = 0; // spath index
	bool stop = spath.empty();
	while (!stop) {
		std::vector<FatFileEntry> dirents = this->get_dir_entries(current_path.cluster);
		for (int j = 0; j < dirents.size(); j++) {
			printf("i: %d | j: %d\n", i , j);
			if (u16bytestostr(dirents[j].lfn.name) == spath[i]) { // found
				current_path.exists = true;
				current_path.path /= spath[i];
				current_path.pclusters.push_back(current_path.cluster);
				current_path.cluster = dirents[j].msdos.firstCluster;					
				current_path.is_dir = dirents[j].msdos.is_dir;
				if (i == spath.size() - 1)  // last entry
					return current_path;
				else // not last entry
					i++;
			}
			else {
				current_path.exists = false;
			}
		}
		if (this->fat_table[current_path.cluster] == FAT_ENTRY_EOC)
			stop = true;
		else if (!current_path.exists) 
			current_path.cluster = this->fat_table[current_path.cluster];			
	}
}


std::vector<FatFileEntry> Fat32Image::get_dir_entries(int cluster_id) {
	std::vector<FatFileEntry> entries;
	if (cluster_id < 2)
		return entries;
	int fd = open(this->image_file.c_str(), O_RDONLY);
	printf("--cluster #%d @ %u\n", cluster_id, cluster2byte(cluster_id));
	bool cond = true;
	uint8_t is_allocated;
	off_t cur_offset = this->cluster2byte(cluster_id);
	while (cond) {
		entries.emplace_back(read_dir_entry(fd, cur_offset));
		cur_offset = lseek(fd, 0, SEEK_CUR);
		read(fd, &is_allocated, 1);
		if (is_allocated == 0)
			cond = false;
		else
			lseek(fd, cur_offset, SEEK_SET);
	}
	close(fd);
	printf("len entries: %d\n", entries.size());
	
	// FatFileEntry entry = entries[1];

	// printf(
	// 	"fname: %s.%s\n"
	// 	"name: '%s'\n"
	// 	"seq-no: %02x\n"
	// 	"csum: %u\n"
	// 	"creationtimems: %u\n"
	// 	"fileSize: %u\n"
	// 	"seq_is_last: %d\n"
	// 	"seq-no: %d\n"
	// 	"is dir?: %d\n"
	// 	"ea index: %04x\n"
	// 	"first cluster: %04x\n"
	// 	"file-access: %s\n",
	// 	entry.msdos.filename,
	// 	entry.msdos.extension,
	// 	u16bytestostr(entry.lfn.name).c_str(),
	// 	entry.lfn.sequence_number,
	// 	entry.lfn.checksum,
	// 	entry.msdos.creationTimeMs,
	// 	entry.msdos.fileSize,
	// 	entry.lfn.seq_is_last,
	// 	entry.lfn.seq_no,
	// 	entry.msdos.is_dir,
	// 	entry.msdos.eaIndex,
	// 	entry.msdos.firstCluster,
	// 	entry.msdos.file_desc
	// );

	// uint8_t time_arr[3];
	// uint8_t date_arr[3];
	// ustrtime(entry.msdos.modifiedTime, time_arr);
	// ustrdate(entry.msdos.modifiedDate, date_arr);
	// printf("%u/%u/%u %u:%u:%u\n", 
	// 	date_arr[0], date_arr[1], date_arr[2],
	// 	time_arr[0], time_arr[1], time_arr[2]);

	return entries;
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

int Fat32Image::cluster2byte(int cluster_id) {
	return this->data_area_start + (cluster_id - 2) * sector2byte(this->BPB.SectorsPerCluster);
}

int Fat32Image::sector2byte(int sector_id) {
	return sector_id * this->BPB.BytesPerSector;
}
