#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "fat32.h"


void read_fat_table(int fd, int start, int end, uint32_t *fat_table) {
	int total_entries = (end - start) / 4;
	lseek(fd, start, SEEK_SET);
	read(fd, fat_table, end - start);
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

	read(fd, &fat_entry.lfn, 32);
	read(fd, &fat_entry.msdos, 32);

	switch(fat_entry.msdos.filename[0]) {
		case 0:		//free
			fat_entry.state = 0;
			break;
		case 0xe5:	// erased
			fat_entry.state = 2;	
			break;
		default:	// used
			fat_entry.state = 1;
	}

	for (int i = 0; i < 13; i++) {
		if (i<5)
			fat_entry.name[i+1] = fat_entry.lfn.name1[i];
		else if (i<11) 
			fat_entry.name[i+1] = fat_entry.lfn.name2[i-5];
		else
			fat_entry.name[i+1] = fat_entry.lfn.name3[i-11];
	}

	fat_entry.seq_is_last = (fat_entry.lfn.sequence_number & FAT_DIRENT_SEQLAST_MASK) == FAT_DIRENT_SEQLAST ? true : false;
	fat_entry.seq_no = fat_entry.lfn.sequence_number & FAT_DIRENT_SEQNO_MASK;

	if (fat_entry.msdos.filename[0] == FAT_DIRENT_DOT) {
		if (fat_entry.msdos.filename[1] == FAT_DIRENT_DOT) 
			fat_entry.is_dir = 3;
		else
			fat_entry.is_dir = 2;
	}
	else 
		fat_entry.is_dir = fat_entry.msdos.attributes & FAT_DIRENT_ISDIR ? 1 : 0;

	u16strdatetime(fat_entry.msdos.modifiedDate, fat_entry.msdos.modifiedTime, fat_entry.datetime_str);

	// ..., since the FAT32 filesystem does not support file permissions, 
	// file ownership, and links, the beginning is fixed.
	const char *access[] = {"-", "d"};
	sprintf(
		fat_entry.file_desc,
		"%srwx------ 1 root root",
		(fat_entry.is_dir ? access[1] : access[0]));

	return fat_entry;
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