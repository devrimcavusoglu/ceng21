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

	fs::path get_cwd();

	// cd into given path. Returns true if valid, false otherwise.
	void change_directory(fs::path path);

private:
	void read_bpb();

	uint32_t get_fat_entry(int entry_id);

	FatFileEntry get_dir_entry(int entry_id);

	void read_cluster(int cluster_id, void *buf);

	int cluster2sector(int cluster_id);
	
	int sector2byte(int sector_id);

	int cluster2byte(int cluster_id);

	// attributes
	fs::path image_file; // file path
	BPB_struct BPB;

	int fat_entry_offset; // FAT table offset (bytes)
	int data_area_start; // Data area offset (sector)
	unsigned int cluster_size; // Cluster size in bytes

	fs::path cwd;
};