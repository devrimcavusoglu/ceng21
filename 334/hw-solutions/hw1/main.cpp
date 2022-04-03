#include <cstdio>
#include <iostream>
#include <string>

#include "parser.c"


int main() {
	int sts;
	parsed_input *p;
	std::string input;
	char *init_line;

	bool input_marker = true;
	short is_bundle_creation = 0;

	while (true) {
		if (input_marker) std::cout << ">>> ";
		else std::cout << "(c) ";

		std::getline(std::cin >> std::ws, input);
		
		init_line = input.append("\n").data();
		sts = parse(init_line, is_bundle_creation, p);

		if (p->command.type == command_type::QUIT) return 0;
		else if (p->command.type == command_type::PROCESS_BUNDLE_CREATE) {
			// PB Creation Start
			input_marker = false;
			is_bundle_creation = 1;
		}
		else if (p->command.type == command_type::PROCESS_BUNDLE_STOP) {
			// PB Creation End
			input_marker = true;
			is_bundle_creation = 0;
		}
		else {
			// Execution
			if (is_bundle_creation) {
			}
			else {
			}
		}
		std::cout << "#################\n";
		std::cout << "sts: " << sts << std::endl;
		std::cout << "Type: " << p->command.type << std::endl;
		std::cout << "Name: " << p->command.bundle_name << std::endl;
		std::cout << "Count: " << p->command.bundle_count << std::endl;

		
	}
}
