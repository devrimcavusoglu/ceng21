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
	this->get_dir_entries(2);
	// this->get_dir_entry(3);
	// this->get_dir_entry(4);
	// this->get_dir_entry(5);
	// uint8_t buf[1024];
	// this->read_cluster(root_dir.msdos.firstCluster, buf); // root
	// printf("buf: %\n", buf);
}

// Private members

path_t Fat32Image::locate(fs::path path) {
	path_t current_directory = this->cwd;
	std::vector<std::string> spath = tokenizeStringPath(path);

	if (spath[0] == ".." and !current_directory.pclusters.empty()) {
		current_directory.path = current_directory.path.parent_path();
		current_directory.cluster = current_directory.pclusters.back();
		current_directory.pclusters.pop_back();
	}
	else 
		current_directory = this->root;

	while (this->fat_table[current_directory.cluster] != FAT_ENTRY_EOC) {

	}
}


std::vector<FatFileEntry> Fat32Image::get_dir_entries(int cluster_id) {
	std::vector<FatFileEntry> entries;
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
	
	// FatFileEntry entry = entries[0];

	// printf(
	// 	"fname: %s.%s\n"
	// 	"name: '%s'\n"
	// 	"seq-no: %02x\n"
	// 	"csum: %u\n"
	// 	"creationtimems: %u\n"
	// 	"fileSize: %u\n"
	// 	"seq_is_last: %d\n"
	// 	"seq-no: %d\n"
	// 	"is dir?: %d\n",
	// 	entry.msdos.filename,
	// 	entry.msdos.extension,
	// 	utf16bytestostr(entry.lfn.name).c_str(),
	// 	entry.lfn.sequence_number,
	// 	entry.lfn.checksum,
	// 	entry.msdos.creationTimeMs,
	// 	entry.msdos.fileSize,
	// 	entry.lfn.seq_is_last,
	// 	entry.lfn.seq_no,
	// 	entry.msdos.is_dir
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
	return this->data_area_start + (cluster_id - 2) * this->BPB.SectorsPerCluster;
}

int Fat32Image::sector2byte(int sector_id) {
	return sector_id * this->BPB.BytesPerSector;
}
