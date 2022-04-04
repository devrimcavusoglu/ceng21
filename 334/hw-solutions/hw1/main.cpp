#include <cstdio>
#include <iostream>
#include <string>
#include <utility>
#include <iomanip>

#include "parser.h"
#include "bundle.h"


int main() {
	int sts;
	parsed_input *p = new parsed_input;
	std::string input;
	char *init_line;

	bool input_marker = true;
	short is_bundle_creation = 0;
	BundleControlBlock bcb;
	ProcessBundle *pb = NULL;

	while (true) {
		if (input_marker) std::cout << ">>> ";
		else std::cout << "# ";

		std::getline(std::cin >> std::ws, input);
		
		init_line = input.append("\n").data();
		sts = parse(init_line, is_bundle_creation, p);

		if (p->command.type == command_type::QUIT) {
			delete p;
			delete pb;
			return 0;
		}
		else if (p->command.type == command_type::PROCESS_BUNDLE_CREATE) {
			// PB Creation Start
			input_marker = false;
			is_bundle_creation = 1;
			pb = new ProcessBundle(p->command.bundle_name);
		}
		else if (p->command.type == command_type::PROCESS_BUNDLE_STOP) {
			// PB Creation End
			input_marker = true;
			is_bundle_creation = 0;
			if (pb) bcb.add(pb);
		}
		else {
			// Execution
			if (is_bundle_creation && pb) {
				pb->addCommand(input);
			}
			else {
			}
		}
		/*std::cout << "sts: " << sts << std::endl;
		std::cout << "Type: " << p->command.type << std::endl;
		std::cout << "Name: " << p->command.bundle_name << std::endl;
		std::cout << "Count: " << p->command.bundle_count << std::endl;*/
		std::cout << bcb.count() << ", " << pb->count() <<  std::endl;
	}
}
