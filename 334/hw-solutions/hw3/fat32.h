#ifndef HW3_FAT32_H
#define HW3_FAT32_H

#include <stdint.h>
#include <stdlib.h>

// Bytes per sector is fixed at 512 in this homework.
#define BPS 512

#define FAT_ENTRY_MASK 0x0fffffff

#define FAT_ENTRY_BAD 0x0ffffff7
#define FAT_ENTRY_EOC 0x0ffffff8

// Assuming all dirents 64 bytes (1 LFN + FAT32) 
// This assumption will fail for entries where `# of LFN entries > 1`
#define FAT_DIRENT_PER_CLUSTER 1024/64  

#define FAT_DIRENT_DELETED 0xe5
#define FAT_DIRENT_SEQLAST 0x40
#define FAT_DIRENT_SEQNO_MASK 0xf
#define FAT_DIRENT_SEQLAST_MASK 0xf0
#define FAT_DIRENT_ISDIR 0x10
#define FAT_DIRENT_DOT 0x2e
#define FAT_DIRENT_TILDA 0x7e
#define FAT_DIRENT_SHORTNAME_START 0x31
#define FAT_DIRENT_SHORTNAME_PAD 0x20
#define FAT_DIRENT_EAINDEX_MASK 0xffff0000
#define FAT_DIRENT_FIRSTCLUSTER_MASK 0xffff

#define FAT_FILE_TIME_HOUR_MASK 0x1f
#define FAT_FILE_TIME_MINUTE_MASK 0x3f
#define FAT_FILE_TIME_SECOND_MASK 0x1f

#define FAT_FILE_DATE_YEAR_MASK 0x7f
#define FAT_FILE_DATE_MONTH_MASK 0xf
#define FAT_FILE_DATE_DAY_MASK 0x1f


#pragma pack(push, 1)
// Starting at offset 36 into the BIOS Parameter Block (BRB) for FAT32
typedef struct struct_BPBFAT32_struct {
    uint32_t FATSize;              // Logical sectors per FAT. Size: 4 bytes
    uint16_t ExtFlags;             // Drive description/Mirroring flags. Size: 2 bytes
    uint16_t FSVersion;            // Version. Size: 2 bytes.
    uint32_t RootCluster;          // Cluster number of root directory start. Typically it is two. Size: 4 bytes.
    uint16_t FSInfo;               // Logical sector number of FS Information sector on FAT32. Size: 2 bytes
    uint16_t BkBootSec;            // First logical sector number of a copy of the three FAT32 boot sectors. It is typically 6. Size: 2 bytes
    uint8_t Reserved[12];          // Reserved bytes. (Previously used by MS-DOS utility FDISK). Size: 12 byte
    uint8_t BS_DriveNumber;        // Physical drive number. Size: 1 byte
    uint8_t BS_Reserved1;          // Reserved. Used for various purposes on FAT12/16 systems. Size: 1 byte
    uint8_t BS_BootSig;            // Boot signature. 0x26 for FAT12/16, 0x29 for FAT32. Size: 1 byte
    uint32_t BS_VolumeID;          // Volume ID. (Mostly for FAT12/16). Size: 4 bytes
    uint8_t BS_VolumeLabel[11];    // Volume Name. (Not really important). Size: 11 bytes.
    uint8_t BS_FileSystemType[8];  // File system type. Padded with spaces at the end. In our case it will be "FAT32   ". Size: 8 bytes
} BPB32_struct;

typedef struct struct_BPB_struct {

    uint8_t BS_JumpBoot[3];        // Jump Instruction. Size: 3 bytes
    uint8_t BS_OEMName[8];         // The system that formatted the disk. Size: 8 bytes
    uint16_t BytesPerSector;       // Bytes per logical sector (It is always will be 512 in our case). Size: 2 bytes
    uint8_t SectorsPerCluster;     // Logical sectors per cluster in the order of two. Size: 1 byte
    uint16_t ReservedSectorCount;  // Count of reserved logical sectors. Size: 2 bytes
    uint8_t NumFATs;               // Number of file allocation tables. Default value is two but can be higher. Size: 1 byte
    uint16_t RootEntryCount;       // Maximum number of FAT12 or FAT16 directory entries. It is 0 for FAT32. Size: 2 bytes
    uint16_t TotalSectors16;       // Total logical sectors. It is 0 for FAT32. Size: 2 bytes
    uint8_t Media;                 // Media descriptor. Size: 1 byte
    uint16_t FATSize16;            // Logical sectors per FAT for FAT12/FAT16. It is 0 for FAT32. Size: 2 bytes
    uint16_t SectorsPerTrack;      // Not relevant
    uint16_t NumberOfHeads;        // Not relevant
    uint32_t HiddenSectors;        // Not relevant
    uint32_t TotalSectors32;       // Total logical sectors including the hidden sectors
    BPB32_struct extended;         // Extended parameters for FAT32
} BPB_struct;

typedef struct struct_FatFile83 {
    uint8_t filename[8];           // Filename for short filenames. First byte have special values.
    uint8_t extension[3];          // Remaining part used for file extension
    uint8_t attributes;            // Attributes
    uint8_t reserved;               // Reserved to mark extended attributes
    uint8_t creationTimeMs;        // Creation time down to ms precision
    uint16_t creationTime;         // Creation time with H:M:S format
    uint16_t creationDate;         // Creation date with Y:M:D format
    uint16_t lastAccessTime;       // Last access time
    uint16_t eaIndex;              // Used to store first two bytes of the first cluster
    uint16_t modifiedTime;         // Modification time with H:M:S format
    uint16_t modifiedDate;         // Modification date with Y:M:D format
    uint16_t firstCluster;         // Last two bytes of the first cluster
    uint32_t fileSize;             // Filesize in bytes
} FatFile83;

// The long filename information can be repeated as necessary before the original 8.3 filename entry
typedef struct struct_FatFileLFN {
    uint8_t sequence_number;
    uint16_t name1[5];      // 5 Chars of name (UTF-16 format)
    uint8_t attributes;     // Always 0x0f
    uint8_t reserved;       // Always 0x00
    uint8_t checksum;       // Checksum of DOS Filename. Can be calculated with a special formula.
    uint16_t name2[6];      // 6 More chars of name (UTF-16 format)
    uint16_t firstCluster;  // Always 0x0000
    uint16_t name3[2];      // 2 More chars of name (UTF-16 format)
} FatFileLFN;

#pragma pack(pop)

typedef struct struct_FatFileEntry {
    FatFile83 msdos;
    FatFileLFN lfn;
    uint8_t state;                 // 0: free 1: used 2: erased
    uint8_t is_dir;                // 0: file 1: dir 2: dot-dir 3: dotdot-dir
    char file_desc[22];            // File access rights as char array    
    char datetime_str[13];         // Date-time as string
    uint16_t name[14];             // name1 + name2 + name3
    bool seq_is_last;              // Whether entry is last LFN sequence or not
    uint8_t seq_no;                // LFN sequence number
} FatFileEntry;


void read_fat_table(int fd, int start, int end, uint32_t *fat_table);

void u16strdatetime(uint16_t date, uint16_t time, char *buffer);

void get_month(uint8_t month, char *buffer);

uint32_t read_fat_entry(int fd, int offset);

FatFileEntry read_dir_entry(int fd, int offset);

void read_data(int fd, int offset, void *buf, unsigned int size);

unsigned char cksum(unsigned char *pFcbName);

#endif //HW3_FAT32_H
