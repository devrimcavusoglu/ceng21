#include <stdio.h>

#include "image.hpp"


void Fat32Image::read(std::string path) {
	printf("Im here..");
	FILE *fp = fopen(path.data(), "rb");
	char buffer[BPS];
	while (fgets(buffer, BPS, fp)) {
		printf("%s\n", buffer[0]);
		break;
	}
}