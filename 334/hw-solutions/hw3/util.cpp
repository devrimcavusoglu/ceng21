#include "fat32.h"
#include "util.hpp"


std::string u16bytestostr(uint16_t *chars, int start) {
    std::string strname;
    if (chars[0] == FAT_DIRENT_DOT) 
        strname = ".";
    else if (chars[1] == FAT_DIRENT_DOT)
        strname = "..";
    else {
        for (size_t i = start; i <= sizeof(chars); i++) {
            if (chars[i] == 0) // Char bytes termination
                break;
            strname += chars[i];
        }
    }
    return strname;
}


void strtou16bytes(std::string str, uint16_t *buffer, int n) {
    const char *c_str = str.c_str();

    for (size_t i = 0; i < n; i++) {
        buffer[i] = c_str[i];
    }
}


void correct_u16bytes(const char *src, char *dest) {
    for (int i = sizeof(dest)-1; i >= 0; i--) {
        if (i%2 != 0) {
            dest[i] = 0;
            continue;
        }
        dest[i] = src[i/2];
    }
}

std::vector<std::string> tokenizeStringPath(std::string p) {
    int pos = -1;
    std::vector<std::string> v;
    while((pos = p.find('/'))!=-1){
        std::string dir = p.substr(0, pos);
        v.push_back(dir);
        p = p.substr(pos+1);
    };

    if(p.size()){
        v.push_back(p);
    }

    return v;
}


std::tm *get_time() {
    std::time_t t = std::time(0);   // get time now
    std::tm* now = std::localtime(&t);
    return now;
}

uint16_t uformattime(std::tm *datetime, bool time) {
    if (time) {
        uint16_t hour = datetime->tm_hour;
        uint16_t minute = datetime->tm_min;
        uint16_t second = datetime->tm_sec;
        return (hour << 11) + (minute << 5) + second/2;
    }
    else {
        uint16_t year = datetime->tm_year - 1980;
        uint16_t month = datetime->tm_mon;
        uint16_t day = datetime->tm_mday;
        return (year << 9) + (month << 5) + day;   
    }
}


void fix_filename_digits(unsigned char *filename, unsigned int offset) { 
    filename[0] = FAT_DIRENT_TILDE;
    int name_id = FAT_DIRENT_SHORTNAME_START + (offset/64);
    int pad_start = 2;

    if (name_id >= 0x3a) {
        name_id = name_id - FAT_DIRENT_SHORTNAME_OFFSET;
        uint8_t first_digit, second_digit;
        first_digit = floor(name_id / 10);
        second_digit = name_id % 10;

        filename[1] = FAT_DIRENT_SHORTNAME_OFFSET + first_digit;
        filename[2] = FAT_DIRENT_SHORTNAME_OFFSET + second_digit;
        pad_start = 3;
    } 
    else {
        filename[1] = name_id;
    }
    for (int i = pad_start; i<sizeof(filename); i++)
            filename[i] = FAT_DIRENT_SHORTNAME_PAD;
}
