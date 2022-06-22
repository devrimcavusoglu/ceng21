#include <stdlib.h>
#include <stdio.h>
#include <string.h>


unsigned int_to_int(unsigned int k) {
    char buffer[65]; /* any number higher than sizeof(unsigned int)*bits_per_byte(8) */
    snprintf(buffer, sizeof(buffer), "%d", k);
    return atoi(buffer);
}

template <class T>
std::string bytes2str(T *bytes) {
	int n = sizeof(bytes);
	char chars[n+1];
    memcpy(chars, bytes, n);
    chars[n] = '\0';
    std::string s(chars);
    return s;
}
