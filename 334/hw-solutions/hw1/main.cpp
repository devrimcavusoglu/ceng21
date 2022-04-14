#include <cstdio>
#include <iostream>
#include <string>
#include <utility>
#include <iomanip>

#include "parser.h"
#include "bcb.h"
#include "bundle.h"


void single_execution(ProcessBundle *pb, char *in, char *out) {
	int fd_in;
	int fd_out;
	std::string capture;

	if (in) {
		std::cout << "input: " << in << std::endl;
		fd_in = open(in, O_RDONLY);	
	}
	else
		fd_in = -1;
	
	if (out) 
		fd_out = open(out, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	else
		fd_out = -1;

	capture = pb->execute(fd_in, fd_out);
}


void execute(parsed_input *p, BundleControlBlock &bcb) {
	int bcount = p->command.bundle_count;
	if (bcount == 1) {
		char *pb_name = p->command.bundles[0].name;
		char *in = p->command.bundles[0].input;
		char *out = p->command.bundles[0].output;
		ProcessBundle *pb = bcb.get(pb_name);
		single_execution(pb, in, out);
		return;
	}

	/*multiple_execution();
	if (in) {
		std::cout << "input: " << in << std::endl;
		int fd_in = open(in, O_RDONLY);
		input = pb->readFromFD(fd_in);
	}
	for (int i = 0; i < bcount; i++) {
		char *pb_name = p->command.bundles[i].name;
		char *in = p->command.bundles[i].input;
		char *out = p->command.bundles[i].output;

		ProcessBundle *current = bcb.get(pb_name);
		if (!current) {
			std::cout << "Unknown bundle: '" << pb_name << "'\n";
			continue;
		}

		current->execute(in, out);
		if (out) {
			int fd_out = open(out, O_WRONLY | O_TRUNC | O_CREAT, 0644);
			write(fd_out, content.data(), content.size());
			close(fd_out);
		}
		else {
			std::cout << content;
		}
	}*/
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
		if (input == "clear")
			system("clear");
		
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
			if (bcb.exists(p->command.bundle_name))
				pb = bcb.get(p->command.bundle_name);
			else
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
			if (is_bundle_creation and pb) {
				pb->addCommand(input);
			}
			else {
				execute(p, bcb);
			}
		}
	}
}
