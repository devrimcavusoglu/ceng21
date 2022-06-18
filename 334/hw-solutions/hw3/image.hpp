#include <string>
#include <vector>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <iostream>
#include <unistd.h>

#include "fat32.h"


class Fat32Image {
public:
	Fat32Image() {}
	// reads the image from given path and parses the image.
	void read_image(char *path);

private:
	void read_bpb(int fd);

	void read_ebpb(int fd);

	BPB_struct bpb;
	BPB32_struct ebpb;
	std::vector<FatFileEntry> file_entries;
};