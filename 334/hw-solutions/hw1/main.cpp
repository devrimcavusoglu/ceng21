#include <cstdio>
#include <iostream>
#include <string>
#include <utility>
#include <iomanip>

#include "parser.h"
#include "bundle.h"


void execute(parsed_input *p, BundleControlBlock &bcb) {
	int bcount = p->command.bundle_count;
	for (int i = 0; i < bcount; i++) {
		char *pb_name = p->command.bundles[i].name;
		char *out = p->command.bundles[i].output;
		char *in = p->command.bundles[i].input;
		ProcessBundle *current = bcb.get(pb_name);
		if (current) std::cout << current->name << std::endl;
		else std::cout << "Unknown bundle: '" << pb_name << "'\n";
		if (out) std::cout << out << std::endl; 
		if (in) std::cout << in << std::endl;
	}
}


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

		if (input == "ls") {
			for (int i = 0; i < bcb.count(); i++) {
				std::string pb_name = bcb.bundles[i]->name;
				std::cout << "PB name: " << pb_name << std::endl;
			}
			continue;
		}
		
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
		else if (p->command.type == command_type::PROCESS_BUNDLE_EXECUTION){
			// Execution
			if (is_bundle_creation && pb) {
				pb->addCommand(input);
			}
			else {
				execute(p, bcb);
			}
		}
		/*std::cout << "sts: " << sts << std::endl;
		std::cout << "Type: " << p->command.type << std::endl;
		std::cout << "Name: " << p->command.bundle_name << std::endl;
		std::cout << "Count: " << p->command.bundle_count << std::endl;
		std::cout << bcb.count() << ", " << pb->count() <<  std::endl;*/
	}
}
