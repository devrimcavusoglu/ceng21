#ifndef _IMAGE_HPP_
#define _IMAGE_HPP_

#include <filesystem>
#include <fcntl.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

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
	uint32_t get_fat_entry(int entry_id);

	FatFileEntry get_dir_entry(int cluster_id);

	void get_data(int cluster_id, void *buf);

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

#endif //_IMAGE_HPP_