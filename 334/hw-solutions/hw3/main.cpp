#include <iostream>
#include <string>

#include "parser.h"
#include "image.hpp"


int main(int argc, char **argv) {
	if (argc == 1) {
		std::cerr << "Image file is not provided.\n"; 
		exit(-1);
	}
	else if (argc > 2) {
		std::cerr << "Provide only a single argument path.\n"; exit(-1);
	}
	char *image_file = argv[1];
	Fat32Image fat32img(image_file);

	parsed_input *p = new parsed_input;
	std::string input;

	bool input_marker = true;

	while (true) {
		// Used to prompt markers for inputs and CWD
		if (input_marker) std::cout << fat32img.get_cwd().c_str() << "> ";

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
		std::string arg1 = (p->arg1) ? p->arg1 : "";
		std::string arg2 = (p->arg2) ? p->arg2 : "";

		switch(p->type) {
			case input_type::CD:	// Change directory
				if (arg1 != "")
					fat32img.change_directory(arg1);
				break;

			case input_type::LS:	// List directory
				if (arg1 == "-l") {
					if (arg2 == "")
						arg2 = ".";
					fat32img.list_directory(arg2, true);
				}
				else {
					if (arg1 == "")
						arg1 = ".";
					fat32img.list_directory(arg1);
				}
				break;

			case input_type::CAT:	// Concat & print file content
				if (arg1 != "")
					fat32img.cat_file(arg1);
				break;
			
			case input_type::TOUCH:
				if (arg1 != "")
					fat32img.touch(arg1);
				break;
		}
	}
}