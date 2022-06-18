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
}


void Fat32Image::read_bpb(int fd) {
	read(fd, bpb.BS_JumpBoot, 3);
	read(fd, bpb.BS_OEMName, 8);
	read(fd, &bpb.BytesPerSector, 2);

	printf("%d\n", bpb.BytesPerSector);
}