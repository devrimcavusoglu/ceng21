#include "fat32.h"
#include "util.hpp"


std::string u16bytestostr(uint16_t *chars) {
    std::string strname;
    if (chars[0] == FAT_DIRENT_DOT) 
        return ".";
    else if (chars[1] == FAT_DIRENT_DOT)
        return "..";
    
    for (size_t i = 0; i <= sizeof(chars); i++) {
        if (chars[i] == 0) // Char bytes termination
            break;
        strname += chars[i];
    }
    return strname;
}


std::vector<std::string> tokenizeStringPath(std::string p) {
    /**
     * Converts the path 'p' into tokenized set of strings. p needs to be a path string, e.g. "/home/a/b/c.txt".
     * 
     * Returns: vector<string>
     * 
     * You also have the option to get "/" as the root element, instead of an empty string "". Check the .cpp file for that.
     */
    int pos = -1;
    std::vector<std::string> v;
    while((pos = p.find('/'))!=-1){
        std::string dir = p.substr(0, pos);
        v.push_back(dir);
        p = p.substr(pos+1);
    };

    //* uncomment if you want to have / for paths starting from root. Currently it is ""(empty string) instead of "/"
    // if(v.size()){
    //  if(v[0] == ""){
    //      v[0]="/";
    //  }
    // }

    if(p.size()){
        v.push_back(p);
    }

    return v;
}