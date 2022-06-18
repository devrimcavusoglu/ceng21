#include <algorithm>
#include <stdlib.h>

#include "image.hpp"

bool all_zero(char *chararray) {
	int len = sizeof(chararray) / sizeof(chararray[0]);
	printf("len: %d\n", len);
	for (int i = 0; i < len; i++) {
		if (chararray[i] != 0)
			return false;
	}
	return true;
}


void Fat32Image::read_image(char *path) {
	printf("receieved path: %s\n", path);
	int fd = open(path, O_RDONLY);
	this->read_bpb(fd);
	this->read_ebpb(fd);
}


void Fat32Image::read_bpb(int fd) {
	read(fd, bpb.BS_JumpBoot, 3);
	read(fd, bpb.BS_OEMName, 8);
	read(fd, &bpb.BytesPerSector, 2);
	read(fd, &bpb.SectorsPerCluster, 1);
	read(fd, &bpb.ReservedSectorCount, 2);
	read(fd, &bpb.NumFATs, 1);
	read(fd, &bpb.RootEntryCount, 2);
	read(fd, &bpb.TotalSectors16, 2);
	read(fd, &bpb.Media, 1);
	read(fd, &bpb.FATSize16, 2);
	read(fd, &bpb.SectorsPerTrack, 2);
	read(fd, &bpb.NumberOfHeads, 2);
	read(fd, &bpb.HiddenSectors, 4);
	read(fd, &bpb.TotalSectors32, 4);
}


void Fat32Image::read_ebpb(int fd) {
	read(fd, &ebpb.FATSize, 4);
	read(fd, &ebpb.ExtFlags, 2);
	read(fd, &ebpb.FSVersion, 2);
	read(fd, &ebpb.RootCluster, 4);
	read(fd, &ebpb.FSInfo, 2);
	read(fd, &ebpb.BkBootSec, 2);
	read(fd, ebpb.Reserved, 12);
	read(fd, &ebpb.BS_DriveNumber, 1);
	read(fd, &ebpb.BS_Reserved1, 1);
	read(fd, &ebpb.BS_BootSig, 1);
	read(fd, &ebpb.BS_VolumeID, 4);
	read(fd, ebpb.BS_VolumeLabel, 11);
	read(fd, ebpb.BS_FileSystemType, 8);

	printf("%d %d %d %d\n", ebpb.FATSize, ebpb.ExtFlags, ebpb.FSVersion, ebpb.RootCluster);
	printf("%d\n", ebpb.BkBootSec);
}