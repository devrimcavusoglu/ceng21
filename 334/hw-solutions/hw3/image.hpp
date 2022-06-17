#include <string>
#include <vector>

#include "fat32.h"


class Fat32Image {
public:
	// reads the image from given path and parses the image.
	void read(std::string path);
private:
	BPB32_struct bpb;
	BPB_struct ebpb;
	std::vector<FatFileEntry> file_entries;
};