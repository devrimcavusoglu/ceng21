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

	if (fat_entry.msdos.filename[0] == FAT_DIRENT_DOT) {
		if (fat_entry.msdos.filename[1] == FAT_DIRENT_DOT) 
			fat_entry.msdos.is_dir = 3;
		else
			fat_entry.msdos.is_dir = 2;
	}
	else 
		fat_entry.msdos.is_dir = fat_entry.msdos.attributes & FAT_DIRENT_ISDIR ? 1 : 0;

	u16strdatetime(fat_entry.msdos.modifiedDate, fat_entry.msdos.modifiedTime, fat_entry.msdos.datetime_str);

	// ..., since the FAT32 filesystem does not support file permissions, 
	// file ownership, and links, the beginning is fixed.
	const char *access[] = {"-", "d"};
	sprintf(
		fat_entry.msdos.file_desc,
		"%srwx------ 1 root root",
		(fat_entry.msdos.is_dir ? access[1] : access[0]));

	return fat_entry;
}


void write_fat_entry(int fd, int offset, FatFileEntry &fat_entry) {
	
}


void read_data(int fd, int offset, void *buf, unsigned int size) {
	lseek(fd, offset, SEEK_SET); // re-position the fd to the offset
	read(fd, buf, size);
}


void u16strdatetime(uint16_t date, uint16_t time, char *buffer) {
    uint8_t month, day, hour, min;
    char month_str[4];

    month = (date >> 5) & FAT_FILE_DATE_MONTH_MASK;
    get_month(month, month_str);
    day = date & FAT_FILE_DATE_DAY_MASK;

    hour = (time >> 11) & FAT_FILE_TIME_HOUR_MASK;
    min = (time >> 5) & FAT_FILE_TIME_MINUTE_MASK;

    sprintf(
			buffer,
			"%s %02u %02u:%02u",
			month_str,
			day,
			hour,
			min);   	
}


void get_month(uint8_t month, char *buffer) {
    switch(month) {
        case 1:
            strcpy(buffer, " Jan");
            break;
        case 2:
            strcpy(buffer, " Feb");
            break;
        case 3:
            strcpy(buffer, " Mar");
            break;
        case 4:
            strcpy(buffer, " Apr");
            break;
        case 5:
            strcpy(buffer, " May");
            break;
        case 6:
            strcpy(buffer, " Jun");
            break;
        case 7:
            strcpy(buffer, " Jul");
            break;
        case 8:
            strcpy(buffer, " Aug");
            break;
        case 9:
            strcpy(buffer, " Sep");
            break;
        case 10:
            strcpy(buffer, " Oct");
            break;
        case 11:
            strcpy(buffer, " Nov");
            break;
        case 12:
            strcpy(buffer, " Dec");
            break;
    }
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