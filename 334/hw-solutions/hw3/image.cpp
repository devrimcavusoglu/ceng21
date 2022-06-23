#include "image.hpp"
#include "util.hpp"

namespace fs = std::filesystem;

// Public members

Fat32Image::Fat32Image(char *path) {
	this->image_file = path;
	int fd = open(this->image_file.c_str(), O_RDONLY);
	read_bpb(fd, this->BPB);
	close(fd);

	this->fat_entry_offset = BPB.ReservedSectorCount * BPB.BytesPerSector;
	this->cluster_size = BPB.BytesPerSector * BPB.SectorsPerCluster;
	this->data_area_start = BPB.ReservedSectorCount + BPB.NumFATs * BPB.extended.FATSize;
	this->cwd = "/"; // set CWD as root

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
}


fs::path Fat32Image::get_cwd() {
	return this->cwd;
}


void Fat32Image::change_directory(fs::path path) {
	std::cout << "path: " << path << std::endl;
	this->get_fat_entry(11);
	this->get_fat_entry(12);
	this->get_dir_entry(2);
	// uint8_t buf[1024];
	// this->read_cluster(root_dir.msdos.firstCluster, buf); // root
	// printf("buf: %\n", buf);
}

// Private members

uint32_t Fat32Image::get_fat_entry(int entry_id) {
	int fd = open(this->image_file.c_str(), O_RDONLY);
	int offset = this->fat_entry_offset + entry_id * 4; // in bytes
	uint32_t res = read_fat_entry(fd, offset);
	close(fd);
	printf("0x%08x\n", res);
	return res;
}

FatFileEntry Fat32Image::get_dir_entry(int cluster_id) {
	int fd = open(this->image_file.c_str(), O_RDONLY);
	FatFileEntry entry = read_dir_entry(fd, this->cluster2byte(cluster_id));
	close(fd);
	// printf(
	// 	"fname: %s\n"
	// 	"name1: %s\n"
	// 	"seq-no: %hhu\n"
	// 	"csum: %hhu\n"
	// 	"creationtimems: %hhu\n",
	// 	entry.msdos.filename,
	// 	entry.lfn.name1,
	// 	entry.lfn.sequence_number,
	// 	entry.lfn.checksum,
	// 	entry.msdos.creationTimeMs
	// );
	uint8_t time_arr[3];
	uint8_t date_arr[3];
	ustrtime(entry.msdos.creationTime, time_arr);
	ustrdate(entry.msdos.creationDate, date_arr);
	printf("%hhu-%hhu-%hhu %hhu:%hhu:%hhu\n", 
		date_arr[0], date_arr[1], date_arr[2],
		time_arr[0], time_arr[1], time_arr[2]);
	return entry;
}

void Fat32Image::get_data(int cluster_id, void *buf) {
	int fd = open(this->image_file.c_str(), O_RDONLY);
	read_data(fd, this->cluster2byte(cluster_id), buf, this->cluster_size);
	close(fd);
}

int Fat32Image::cluster2byte(int cluster_id) {
	return this->sector2byte(this->data_area_start) + cluster_id * this->BPB.SectorsPerCluster;
}

int Fat32Image::sector2byte(int sector_id) {
	return sector_id * this->BPB.BytesPerSector;
}
