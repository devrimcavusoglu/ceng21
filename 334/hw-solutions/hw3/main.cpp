#include <iostream>
#include <string>
#include <filesystem>

#include "parser.h"
#include "image.hpp"

namespace fs = std::filesystem;


int main(int argc, char **argv) {
	if (argc == 1) {
		std::cerr << "Image file is not provided.\n"; 
		exit(-1);
	}
	else if (argc > 2) {
		std::cerr << "Provide only a single argument path.\n"; exit(-1);
	}
	char *image_file = argv[1];
	printf("image_file: %s\n", image_file);
	Fat32Image fat32img;
	fat32img.read_image(image_file);

	// Initially cwd is root '/'
	fs::path cwd = fs::path("/");
	printf("cwd: %s\n", cwd.c_str());

	parsed_input *p = new parsed_input;
	std::string input;

	bool input_marker = true;

	while (true) {
		// Used to prompt markers for inputs and bundle creation
		if (input_marker) std::cout << cwd.c_str() << "> ";

		std::getline(std::cin >> std::ws, input);

		if (input == "clear") {
			system("clear");
			continue;
		}
		else if (input == "quit") {
			delete p;
			exit(0);
		}

		parse(p, input.data());
		std::string arg1 = p->arg1;
		std::string arg2 = p->arg2;

		if (p->type == input_type::CD) {
			if (arg1 == "..") {
				cwd = cwd.parent_path();
			}
			else
				cwd /= p->arg1;
		}
	}
}