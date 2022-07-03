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
	this->cwd.path = "/"; // set CWD as root
	this->cwd.cluster_id = BPB.extended.RootCluster;

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
	return this->cwd.path;
}


void Fat32Image::change_directory(fs::path path) {
	std::cout << "path: " << path << std::endl;
	this->get_dir_entries(2);
	// this->get_dir_entry(3);
	// this->get_dir_entry(4);
	// this->get_dir_entry(5);
	// uint8_t buf[1024];
	// this->read_cluster(root_dir.msdos.firstCluster, buf); // root
	// printf("buf: %\n", buf);
}

// Private members

void Fat32Image::locate(fs::path path) {
	std::vector<std::string> spath = tokenizeStringPath(path);

	if (spath[0] == ".." and cwd.path != "/") {
		cwd.path = cwd.path.parent_path();
	}
	else
		cwd.path = "/";

	// while (this->fat_table[cwd.cluster_id] != FAT_ENTRY_EOC);
}


std::vector<FatFileEntry> Fat32Image::get_dir_entries(int cluster_id) {
	std::vector<FatFileEntry> entries;
	int fd = open(this->image_file.c_str(), O_RDONLY);
	printf("--cluster #%d @ %u\n", cluster_id, cluster2byte(cluster_id));
	bool cond = true;
	uint8_t is_allocated;
	off_t cur_offset;
	while (cond) {
		entries.emplace_back(read_dir_entry(fd, this->cluster2byte(cluster_id)));

		cur_offset = lseek(fd, 0, SEEK_CUR);
		read(fd, &is_allocated, 1);
		if (!is_allocated)
			cond = false;
		else
			lseek(fd, cur_offset, SEEK_SET);
	}
	close(fd);
	printf("len entries: %d\n", entries.size());
	FatFileEntry entry = entries[0];
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

	std::string s = utf16bytestostr(entry.lfn.name1);
	std::cout << s << std::endl;

	printf("is string equal to file: %d\n", (s == "file"));
	printf("is string equal to file1: %d\n", (s == "file1"));
	printf("is string equal to file18: %d\n", (s == "file18"));

	uint8_t time_arr[3];
	uint8_t date_arr[3];
	ustrtime(entry.msdos.modifiedTime, time_arr);
	ustrdate(entry.msdos.modifiedDate, date_arr);
	printf("%u/%u/%u %u:%u:%u\n", 
		date_arr[0], date_arr[1], date_arr[2],
		time_arr[0], time_arr[1], time_arr[2]);
	return entries;
}

std::string Fat32Image::get_cluster(int cluster_id) {
	char buffer[this->bytes_per_cluster];
	int fd = open(this->image_file.c_str(), O_RDONLY);
	read_data(fd, this->cluster2byte(cluster_id), buffer, this->bytes_per_cluster);
	// (!) No null termination to allow string concatenation.
	close(fd);
	std::string content = buffer;
	return content;
}

int Fat32Image::cluster2byte(int cluster_id) {
	return this->data_area_start + (cluster_id - 2) * this->BPB.SectorsPerCluster;
}

int Fat32Image::sector2byte(int sector_id) {
	return sector_id * this->BPB.BytesPerSector;
}
