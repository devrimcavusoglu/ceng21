#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <string>
#include <vector>


std::string u16bytestostr(uint16_t *chars);

void strtou16bytes(std::string str, uint16_t *buffer, int n);

void correct_u16bytes(const char *src, char *dest);


/**
 * Converts the path 'p' into tokenized set of strings. p needs to be a path string, e.g. "/home/a/b/c.txt".
 * 
 * Returns: vector<string>
 * 
 * You also have the option to get "/" as the root element, instead of an empty string "". Check the .cpp file for that.
 */
std::vector<std::string> tokenizeStringPath(std::string p);
