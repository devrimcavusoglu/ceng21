#include <string>
#include <vector>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <iostream>
#include <unistd.h>
#include <filesystem>

#include "fat32.h"

namespace fs = std::filesystem;

class Fat32Image {
public:
	// reads the image from given path and parses the image.
	Fat32Image(char *path);

	// cd into given path. Returns true if valid, false otherwise.
	bool change_directory(fs::path path);

private:
	void read_bpb(int fd);

	void read_ebpb(int fd);

	FatFile83 read_file(int sector_id);

	int cluster2sector(int cluster_id);
	
	int sector2byte(int sector_id);

	// attributes
	fs::path image_file; // file path
	BPB_struct BPB;
	BPB32_struct EBPB;
	std::vector<FatFileEntry> file_entries;
	int data_area_start;
};