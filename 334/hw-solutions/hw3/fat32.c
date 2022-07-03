#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "fat32.h"


void read_fat_table(int fd, int start, int end, uint32_t *fat_table) {
	int total_entries = (end - start) / 4;
	printf("total entries: %d | start: %d | end: %d | current offset: %u\n", 
		total_entries, 
		start,
		end,
		lseek(fd, 0, SEEK_CUR));
	lseek(fd, start, SEEK_SET);
	printf("total entries: %d | current offset: %u\n", 
		total_entries, 
		lseek(fd, 0, SEEK_CUR));
	read(fd, fat_table, end - start);
}


void read_bpb(int fd, BPB_struct &BPB) {
	// BPB
	read(fd, BPB.BS_JumpBoot, 3);
	read(fd, BPB.BS_OEMName, 8);
	read(fd, &BPB.BytesPerSector, 2);
	read(fd, &BPB.SectorsPerCluster, 1);
	read(fd, &BPB.ReservedSectorCount, 2);
	read(fd, &BPB.NumFATs, 1);
	read(fd, &BPB.RootEntryCount, 2);
	read(fd, &BPB.TotalSectors16, 2);
	read(fd, &BPB.Media, 1);
	read(fd, &BPB.FATSize16, 2);
	read(fd, &BPB.SectorsPerTrack, 2);
	read(fd, &BPB.NumberOfHeads, 2);
	read(fd, &BPB.HiddenSectors, 4);
	read(fd, &BPB.TotalSectors32, 4);

	// Extended parameters 
	BPB32_struct EBPB;
	read(fd, &EBPB.FATSize, 4);
	read(fd, &EBPB.ExtFlags, 2);
	read(fd, &EBPB.FSVersion, 2);
	read(fd, &EBPB.RootCluster, 4);
	read(fd, &EBPB.FSInfo, 2);
	read(fd, &EBPB.BkBootSec, 2);
	read(fd, EBPB.Reserved, 12);
	read(fd, &EBPB.BS_DriveNumber, 1);
	read(fd, &EBPB.BS_Reserved1, 1);
	read(fd, &EBPB.BS_BootSig, 1);
	read(fd, &EBPB.BS_VolumeID, 4);
	read(fd, EBPB.BS_VolumeLabel, 11);
	read(fd, EBPB.BS_FileSystemType, 8);
	BPB.extended = EBPB;
}


uint32_t read_fat_entry(int fd, int offset) {
	uint32_t a;
	lseek(fd, offset, SEEK_SET); // re-position the fd to the offset
	read(fd, &a, 4);
	return a & FAT_ENTRY_MASK;
}


FatFileEntry read_dir_entry(int fd, int offset) {
	FatFileEntry fat_entry;
	lseek(fd, offset, SEEK_SET);

	// lfn
	read(fd, &fat_entry.lfn.sequence_number, 1);
	read(fd, fat_entry.lfn.name1, 5*2);
	read(fd, &fat_entry.lfn.attributes, 1);
	read(fd, &fat_entry.lfn.reserved, 1);
	read(fd, &fat_entry.lfn.checksum, 1);
	read(fd, fat_entry.lfn.name2, 6*2);
	read(fd, &fat_entry.lfn.firstCluster, 2);
	read(fd, fat_entry.lfn.name3, 2*2);

	for (int i = 0; i < 13; i++) {
		if (i<5) 
			fat_entry.lfn.name[i] = fat_entry.lfn.name1[i];
		else if (i<11) 
			fat_entry.lfn.name[i] = fat_entry.lfn.name2[i-5];
		else
			fat_entry.lfn.name[i] = fat_entry.lfn.name3[i-11];
	}

	fat_entry.lfn.seq_is_last = (fat_entry.lfn.sequence_number & FAT_DIRENT_SEQLAST_MASK) == FAT_DIRENT_SEQLAST ? true : false;
	fat_entry.lfn.seq_no = fat_entry.lfn.sequence_number & FAT_DIRENT_SEQNO_MASK;

	// msdos
	read(fd, fat_entry.msdos.filename, 8);
	read(fd, fat_entry.msdos.extension, 3);
	read(fd, &fat_entry.msdos.attributes, 1);
	read(fd, &fat_entry.msdos.reserved, 1);
	read(fd, &fat_entry.msdos.creationTimeMs, 1);
	read(fd, &fat_entry.msdos.creationTime, 2);
	read(fd, &fat_entry.msdos.creationDate, 2);
	read(fd, &fat_entry.msdos.lastAccessTime, 2);
	read(fd, &fat_entry.msdos.eaIndex, 2);
	read(fd, &fat_entry.msdos.modifiedTime, 2);
	read(fd, &fat_entry.msdos.modifiedDate, 2);
	read(fd, &fat_entry.msdos.firstCluster, 2);
	read(fd, &fat_entry.msdos.fileSize, 4);

	fat_entry.msdos.is_dir = fat_entry.msdos.attributes & FAT_DIRENT_ISDIR ? true : false;

	return fat_entry;
}

void xread(int fd, void *ptr, unsigned int bytes) {
	int offset = lseek(fd, 0, SEEK_CUR);
	int rc = read(fd, ptr, bytes);
	printf(
		"read %u (%u) bytes.. %u/%u\n", 
		rc,
		bytes, 
		offset,
		lseek(fd, 0, SEEK_CUR)
	);
	// lseek(fd, offset+bytes, SEEK_SET);
}


void read_data(int fd, int offset, void *buf, unsigned int size) {
	lseek(fd, offset, SEEK_SET); // re-position the fd to the offset
	read(fd, buf, size);
}


void ustrtime(uint16_t time, uint8_t *time_array) {
	time_array[0] = time & FAT_FILE_TIME_HOUR_MASK;
	time_array[1] = time & FAT_FILE_TIME_MINUTE_MASK;
	time_array[2] = time & FAT_FILE_TIME_SECOND_MASK;
	time_array[2] *= 2;
	// https://wiki.osdev.org/FAT#Directories_on_FAT12.2F16.2F32
}


void ustrdate(uint16_t date, uint8_t *date_array) {
	date_array[0] = date & FAT_FILE_DATE_YEAR_MASK;
	date_array[1] = date & FAT_FILE_DATE_MONTH_MASK;
	date_array[2] = date & FAT_FILE_DATE_DAY_MASK;
	date_array[0] += 1970;
}


unsigned char cksum (unsigned char *pFcbName)
{
  short FcbNameLen;
  unsigned char Sum;

  Sum = 0;                                                                                                                                                                                           
  for (FcbNameLen = 11; FcbNameLen != 0; FcbNameLen--)
    {   
      // NOTE: The operation is an unsigned char rotate right                 
      Sum = ((Sum & 1) ? 0x80 : 0) + (Sum >> 1) + *pFcbName++;
    }   
  return (Sum);
}