#include <string.h>


template <class T>
std::string bytes2str(T *bytes) {
	int n = sizeof(bytes);
	char chars[n+1];
    memcpy(chars, bytes, n);
    chars[n] = '\0';
    std::string s(chars);
    return s;
}
