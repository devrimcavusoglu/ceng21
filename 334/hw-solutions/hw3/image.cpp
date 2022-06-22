#include <stdlib.h>
#include <sys/types.h>

#include "image.hpp"
#include "util.hpp"

namespace fs = std::filesystem;


// Public members

Fat32Image::Fat32Image(char *path) {
	this->image_file = path;
	this->read_bpb();

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
	int root_dir = this->get_fat_entry(0);
	int root_dir2 = this->get_fat_entry(1);
	int root_dir3 = this->get_fat_entry(2);
	this->get_fat_entry(9);
	int root_dir4 = this->get_fat_entry(10);
	this->get_fat_entry(11);
	this->get_fat_entry(12);

	// uint8_t buf[1024];
	// this->read_cluster(root_dir.msdos.firstCluster, buf); // root
	// printf("buf: %\n", buf);
}

// Private members

void Fat32Image::read_bpb() {
	int fd = open(this->image_file.c_str(), O_RDONLY);

	// BPB
	read(fd, BPB.BS_JumpBoot, 3);
	read(fd, BPB.BS_OEMName, 8);
	read(fd, &BPB.BytesPerSector, 2);
	read(fd, &BPB.SectorsPerCluster, 1);
	read(fd, &BPB.ReservedSectorCount, 2);
	read(fd, &BPB.NumFATs, 1);
	read(fd, &BPB.RootEntryCount, 2);
	read(fd, &BPB.TotalSectors16, 2);
	read(fd, &BPB.Media, 1);
	read(fd, &BPB.FATSize16, 2);
	read(fd, &BPB.SectorsPerTrack, 2);
	read(fd, &BPB.NumberOfHeads, 2);
	read(fd, &BPB.HiddenSectors, 4);
	read(fd, &BPB.TotalSectors32, 4);

	// Extended parameters 
	BPB32_struct EBPB;
	read(fd, &EBPB.FATSize, 4);
	read(fd, &EBPB.ExtFlags, 2);
	read(fd, &EBPB.FSVersion, 2);
	read(fd, &EBPB.RootCluster, 4);
	read(fd, &EBPB.FSInfo, 2);
	read(fd, &EBPB.BkBootSec, 2);
	read(fd, EBPB.Reserved, 12);
	read(fd, &EBPB.BS_DriveNumber, 1);
	read(fd, &EBPB.BS_Reserved1, 1);
	read(fd, &EBPB.BS_BootSig, 1);
	read(fd, &EBPB.BS_VolumeID, 4);
	read(fd, EBPB.BS_VolumeLabel, 11);
	read(fd, EBPB.BS_FileSystemType, 8);
	close(fd);
	BPB.extended = EBPB;
}


uint32_t Fat32Image::get_fat_entry(int entry_id) {
	uint32_t a;

	int offset = this->fat_entry_offset + entry_id * 4;
	printf("offset: %d for entry_id: %d\n", offset, entry_id);
	int fd = open(this->image_file.c_str(), O_RDONLY);

	lseek(fd, offset, SEEK_SET); // re-position the fd to the offset

	read(fd, &a, 4);

	printf("a: 0x%08x\n", a);

	close(fd);
	return a;
}


FatFileEntry Fat32Image::get_dir_entry(int entry_id) {
	FatFileEntry fat_file;

	int offset = this->fat_entry_offset + entry_id * 32;
	printf("offset: %d for entry_id: %d\n", offset, entry_id);
	int fd = open(this->image_file.c_str(), O_RDONLY);
	lseek(fd, offset, SEEK_SET); // re-position the fd to the offset

	// lfn
	read(fd, &fat_file.lfn.sequence_number, 1);
	read(fd, fat_file.lfn.name1, 5);
	read(fd, &fat_file.lfn.attributes, 1);
	read(fd, &fat_file.lfn.reserved, 1);
	read(fd, &fat_file.lfn.checksum, 1);
	read(fd, fat_file.lfn.name2, 6);
	read(fd, &fat_file.lfn.firstCluster, 2);
	read(fd, fat_file.lfn.name3, 2);
	printf(
		"seq-no: %u\n"
		"name1: %s\n"
		"checksum: %u\n",
		fat_file.lfn.sequence_number,
		fat_file.lfn.name1,
		fat_file.lfn.checksum
	);


	// msdos
	read(fd, fat_file.msdos.filename, 8);
	read(fd, fat_file.msdos.extension, 3);
	read(fd, &fat_file.msdos.attributes, 1);
	read(fd, &fat_file.msdos.reserved, 1);
	read(fd, &fat_file.msdos.creationTimeMs, 1);
	read(fd, &fat_file.msdos.creationTime, 2);
	read(fd, &fat_file.msdos.creationDate, 2);
	read(fd, &fat_file.msdos.lastAccessTime, 2);
	read(fd, &fat_file.msdos.modifiedTime, 2);
	read(fd, &fat_file.msdos.modifiedDate, 2);
	read(fd, &fat_file.msdos.firstCluster, 2);
	read(fd, &fat_file.msdos.fileSize, 4);

	close(fd);
	return fat_file;
}

void Fat32Image::read_cluster(int cluster_id, void *buf) {
	int offset = this->cluster2byte(cluster_id);
	printf("offset: %d\n", offset);
	int fd = open(this->image_file.c_str(), O_RDONLY);
	lseek(fd, offset, SEEK_SET); // re-position the fd to the offset
	ssize_t total_read = read(fd, buf, this->cluster_size);
	close(fd);
}


int Fat32Image::cluster2sector(int cluster_id) {
	return this->data_area_start + cluster_id * this->BPB.SectorsPerCluster;
}

int Fat32Image::sector2byte(int sector_id) {
	return sector_id * this->BPB.BytesPerSector;
}

int Fat32Image::cluster2byte(int cluster_id) {
	return this->sector2byte(this->cluster2sector(cluster_id));
}
