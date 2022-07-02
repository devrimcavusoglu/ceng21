#include <iterator>
#include <vector>

#include "image.hpp"
#include "util.hpp"

namespace fs = std::filesystem;

// Public members

Fat32Image::Fat32Image(char *path) {
	this->image_file = path;
	int fd = open(this->image_file.c_str(), O_RDONLY);
	read_bpb(fd, this->BPB);

	this->fat_entry_offset = BPB.ReservedSectorCount * BPB.BytesPerSector;
	this->bytes_per_cluster = BPB.BytesPerSector * BPB.SectorsPerCluster;
	this->data_area_start = this->sector2byte(BPB.ReservedSectorCount + BPB.NumFATs * BPB.extended.FATSize);
	this->cwd = "/"; // set CWD as root

	printf(
		"BPB Information:\n"
		"	BS_JumpBoot: %p\n"
		"	BS_OEMName: %s\n"
		"	BPS: %d\n"
		"	SPC: %d\n"
		"	ReservedSectorCount: %d\n"
		"	NumFATs: %d\n"
		"	RootEntryCount: %d (should be 0)\n"
		"	TotalSectors16: %d (should be 0)\n"
		"	Media: %p\n"
		"	FATSize16: %d (should be 0)\n"
		"	SectorsPerTrack: %d\n"
		"	NumberOfHeads: %d\n"
		"	HiddenSectors: %d\n"
		"	TotalSectors32: %d\n",
		BPB.BS_JumpBoot,
		BPB.BS_OEMName,
		BPB.BytesPerSector,
		BPB.SectorsPerCluster,
		BPB.ReservedSectorCount,
		BPB.NumFATs,
		BPB.RootEntryCount,
		BPB.TotalSectors16,
		BPB.Media,
		BPB.FATSize16,
		BPB.SectorsPerTrack,
		BPB.NumberOfHeads,
		BPB.HiddenSectors,
		BPB.TotalSectors32
	);
	printf(
		"=====================Extended Params=====================\n"
		"	FATSize: %d\n"
		"	ExtFlags: %d\n"
		"	FSVersion: %d\n"
		"	RootCluster: %d\n"
		"	FSInfo: %d\n"
		"	BkBootSec: %d\n"
		"	BS_DriveNumber: %d\n"
		"	BS_Reserved1: %d\n"
		"	BS_BootSig: %d\n"
		"	BS_VolumeID: %u\n"
		"	BS_VolumeLabel: %s\n"
		"	BS_FileSystemType: %s\n"
		"========================================================\n",
		BPB.extended.FATSize,
		BPB.extended.ExtFlags,
		BPB.extended.FSVersion,
		BPB.extended.RootCluster,
		BPB.extended.FSInfo,
		BPB.extended.BkBootSec,
		BPB.extended.BS_DriveNumber,
		BPB.extended.BS_Reserved1,
		BPB.extended.BS_BootSig,
		BPB.extended.BS_VolumeID,
		BPB.extended.BS_VolumeLabel,
		BPB.extended.BS_FileSystemType
	);
	printf("fat entry offset: %d\n", this->fat_entry_offset);
	printf("data area offset: %d\n", this->data_area_start);
	printf("bytes per cluster: %d\n", this->bytes_per_cluster);
	uint32_t fat_table_temp[sector2byte(BPB.extended.FATSize)/4];
	read_fat_table(fd, fat_entry_offset, fat_entry_offset + sector2byte(BPB.extended.FATSize), fat_table_temp);
	this->fat_table = fat_table_temp;
	close(fd);
}


fs::path Fat32Image::get_cwd() {
	return this->cwd;
}


void Fat32Image::change_directory(fs::path path) {
	std::cout << "path: " << path << std::endl;
	this->get_dir_entry(2);
	// this->get_dir_entry(3);
	// this->get_dir_entry(4);
	// this->get_dir_entry(5);
	// uint8_t buf[1024];
	// this->read_cluster(root_dir.msdos.firstCluster, buf); // root
	// printf("buf: %\n", buf);
}

// Private members

FatFileEntry Fat32Image::get_dir_entry(int cluster_id) {
	int fd = open(this->image_file.c_str(), O_RDONLY);
	FatFileEntry entry;
	printf("--cluster #%d @ %u\n", cluster_id, cluster2byte(cluster_id));
	read_dir_entry(fd, this->cluster2byte(cluster_id), entry);
	close(fd);
	printf("seq-no: %d\n", entry.lfn.sequence_number);
	printf(
		"fname: %s.%s\n"
		"name: %s | %s | %s\n"
		"seq-no: %u\n"
		"csum: %u\n"
		"creationtimems: %u\n"
		"fileSize: %u\n",
		entry.msdos.filename,
		entry.msdos.extension,
		entry.lfn.name1,
		entry.lfn.name2, 
		entry.lfn.name3,
		entry.lfn.sequence_number,
		entry.lfn.checksum,
		entry.msdos.creationTimeMs,
		entry.msdos.fileSize
	);
	
	// size_t len16 = 6 * sizeof(uint16_t);
	// size_t len8 = 20;
	// uint16_t *_utf16 = entry.lfn.name2;
	// char utf8[20], *_utf8 = utf8;

	// iconv_t utf16_to_utf8 = iconv_open("UTF-8", "UTF-16");

	// size_t result = iconv(utf16_to_utf8, (char **)&_utf16, &len16, &_utf8, &len8);
	// utf8[19] = '\0';
	// printf("%d - %s\n", (int)result, utf8);

	uint16_t *bytes = entry.lfn.name2;
	char str[101];
	auto p = str;
	p += sprintf(p, "%d", bytes[0]);

	for (int i = 1; i < 7; ++i) {
		p += sprintf(p, ", %d", bytes[i]);
	}
	p[100] = 0;
	puts(str);
    // std::cout << s;


	printf(
		"first byte of fname: 0x%02x\n", entry.msdos.filename[0]
	);
	uint8_t time_arr[3];
	uint8_t date_arr[3];
	ustrtime(entry.msdos.modifiedTime, time_arr);
	ustrdate(entry.msdos.modifiedDate, date_arr);
	printf("%u/%u/%u %u:%u:%u\n", 
		date_arr[0], date_arr[1], date_arr[2],
		time_arr[0], time_arr[1], time_arr[2]);
	return entry;
}

void Fat32Image::get_data(int cluster_id, void *buf) {
	int fd = open(this->image_file.c_str(), O_RDONLY);
	read_data(fd, this->cluster2byte(cluster_id), buf, this->bytes_per_cluster);
	close(fd);
}

int Fat32Image::cluster2byte(int cluster_id) {
	return this->data_area_start + (cluster_id - 2) * this->BPB.SectorsPerCluster;
}

int Fat32Image::sector2byte(int sector_id) {
	return sector_id * this->BPB.BytesPerSector;
}
