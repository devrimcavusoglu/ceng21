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
}


bool Fat32Image::change_directory(fs::path path) {
	FatFile83 fat_file = this->read_file(this->BPB.ReservedSectorCount);
	printf("name: %s\n", fat_file.filename);
	printf("file_size: %d\n", fat_file.fileSize);
	printf("1st cluster: %d\n", fat_file.firstCluster);
	printf("creationTimeMs: %d\n", fat_file.lastAccessTime);
	FatFile83 root_cluster = this->read_file(fat_file.firstCluster);
	printf("name: %s\n", root_cluster.filename);
	printf("file_size: %d\n", root_cluster.fileSize);
	printf("1st cluster: %d\n", root_cluster.firstCluster);
	return false;
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

FatFile83 Fat32Image::read_file(int sector_id) {
	FatFile83 fat_file;

	int offset = this->sector2byte(sector_id);
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


int Fat32Image::cluster2sector(int cluster_id) {
	return cluster_id * this->BPB.SectorsPerCluster;
}

int Fat32Image::sector2byte(int sector_id) {
	return sector_id * this->BPB.BytesPerSector;
}
