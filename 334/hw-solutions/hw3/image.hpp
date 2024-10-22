#ifndef _IMAGE_HPP_
#define _IMAGE_HPP_

#include <filesystem>
#include <fcntl.h>
#include <fstream>
#include <iostream>
#include <ios>
#include <iterator>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <vector>

#include "fat32.h"
#include "util.hpp"


// std::fs is used only for path string management 
// (fs::path object only)
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

	// list directory content
	void list_directory(fs::path path, bool verbose = false);

	// concatante and print file content to stdout 
	void cat_file(fs::path path);

	// makes a new (empty) directory
	void make_directory(fs::path path, FatFileEntry *moved_entry = NULL);

	// makes a new (empty) file
	void touch(fs::path path, FatFileEntry *moved_entry = NULL);

	// move a directory tree/file from src to dest
	void move(fs::path src, fs::path dest);

private:
	path_t locate(fs::path path);

	int cluster_has_space(unsigned int cluster_id);

	void make_entry(fs::path path, bool is_dir = false, FatFileEntry *moved_entry = NULL);

	void mark_deleted(unsigned int cluster_id, std::string name, FatFileEntry &fat_entry);

	// Returns directory entries from cluster content.
	std::vector<FatFileEntry> get_dir_entries(int cluster_id);

	// Returns the raw content of cluster as string.
	std::string get_cluster(int cluster_id);

	uint32_t next_free_cluster();

	int cluster2sector(int cluster_id);
	
	unsigned int sector2byte(unsigned int sector_id);

	unsigned int cluster2byte(unsigned int cluster_id);

	void write_fat_entry(int offset, FatFileEntry fat_entry, bool msdos_only = false);

	void write_dot_entry(int offset, FatFile83 dot_entry);

	void update_fat_table(uint32_t entry_id, uint32_t value);

	// attributes
	fs::path image_file; // file path
	BPB_struct BPB;

	int fat_entry_offset; // FAT table offset (bytes)
	int data_area_start; // Data area offset (bytes)
	unsigned int bytes_per_cluster; // Cluster size (bytes)

	std::vector<uint32_t> fat_table;

	path_t cwd;
	path_t root;
};

#endif //_IMAGE_HPP_