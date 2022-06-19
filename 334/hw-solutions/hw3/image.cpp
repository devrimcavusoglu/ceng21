#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

#include "image.hpp"
#include "util.hpp"

namespace fs = std::filesystem;


// Public members

Fat32Image::Fat32Image(char *path) {
	this->image_file = path;
	int fd = open(path, O_RDONLY);
	this->read_bpb(fd);
	this->read_ebpb(fd);
	close(fd);

	this->fat_entry_offset = BPB.ReservedSectorCount * BPB.BytesPerSector;
	this->cluster_size = BPB.BytesPerSector * BPB.SectorsPerCluster;
	this->data_area_start = BPB.ReservedSectorCount + BPB.NumFATs * EBPB.FATSize;
	this->cwd = "/"; // set CWD as root

	printf("FATSize: %d | RootCluster: %d\n", EBPB.FATSize, EBPB.RootCluster);
	printf(
		"BytesPerSector: %d | SectorsPerCluster: %d | NumFATs: %d | TotalSectors32: %d\n",
		BPB.BytesPerSector,
		BPB.SectorsPerCluster,
		BPB.NumFATs,
		BPB.TotalSectors32
	);
	printf("data area offset: %d\n", this->data_area_start);
}


fs::path Fat32Image::get_cwd() {
	return this->cwd;
}


void Fat32Image::change_directory(fs::path path) {
	std::cout << "path: " << path << std::endl;

}

// Private members

void Fat32Image::read_bpb(int fd) {
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
}


void Fat32Image::read_ebpb(int fd) {
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
}

FatFile83 Fat32Image::read_entry(int entry_id) {
	FatFile83 fat_file;

	int offset = this->fat_entry_offset + entry_id * 32;
	int fd = open(this->image_file.c_str(), O_RDONLY);
	lseek(fd, offset, SEEK_SET); // re-position the fd to the offset
	read(fd, fat_file.filename, 8);
	read(fd, fat_file.extension, 3);
	read(fd, &fat_file.attributes, 1);
	read(fd, &fat_file.reserved, 1);
	read(fd, &fat_file.creationTimeMs, 1);
	read(fd, &fat_file.creationTime, 2);
	read(fd, &fat_file.creationDate, 2);
	read(fd, &fat_file.lastAccessTime, 2);
	read(fd, &fat_file.modifiedTime, 2);
	read(fd, &fat_file.modifiedDate, 2);
	read(fd, &fat_file.firstCluster, 2);
	read(fd, &fat_file.fileSize, 4);
	return fat_file;
}

void Fat32Image::read_cluster(int cluster_id, void *buf) {
	int offset = this->cluster2byte(cluster_id);
	printf("offset: %d\n", offset);
	int fd = open(this->image_file.c_str(), O_RDONLY);
	lseek(fd, offset, SEEK_SET); // re-position the fd to the offset
	ssize_t total_read = read(fd, buf, this->cluster_size);
	printf("%ld | %p\n", total_read, buf);
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
