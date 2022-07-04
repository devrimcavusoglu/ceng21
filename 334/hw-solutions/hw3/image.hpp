#ifndef _IMAGE_HPP_
#define _IMAGE_HPP_

#include <filesystem>
#include <fcntl.h>
#include <iostream>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <vector>

#include "fat32.h"


namespace fs = std::filesystem;


typedef struct struct_path {
	fs::path path;
	uint32_t cluster;
	std::vector<uint32_t> pclusters;
	bool is_dir;
	bool exists;
} path_t;

class Fat32Image {
public:
	// reads the image from given path and parses the image.
	Fat32Image(char *path);

	fs::path get_cwd();

	// cd into given path. Returns true if valid, false otherwise.
	void change_directory(fs::path path);

private:
	path_t locate(fs::path path);

	// Returns directory entries from cluster content.
	std::vector<FatFileEntry> get_dir_entries(int cluster_id);

	// Returns the raw content of cluster as string.
	std::string get_cluster(int cluster_id);

	int cluster2sector(int cluster_id);
	
	int sector2byte(int sector_id);

	int cluster2byte(int cluster_id);

	// attributes
	fs::path image_file; // file path
	BPB_struct BPB;

	int fat_entry_offset; // FAT table offset (bytes)
	int data_area_start; // Data area offset (bytes)
	unsigned int bytes_per_cluster; // Cluster size (bytes)

	uint32_t *fat_table;

	path_t cwd;
	path_t root;
};

#endif //_IMAGE_HPP_