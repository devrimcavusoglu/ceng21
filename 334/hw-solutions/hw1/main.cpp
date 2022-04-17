#include <cstdio>
#include <iostream>
#include <string>
#include <utility>
#include <iomanip>

#include "parser.h"
#include "bcb.h"
#include "bundle.h"


int sanitize_parameters(int i, int bcount, char *in, char *out) {
	int err = 0;
	if ((i > 0 and i < bcount - 1) and (in or out)) {
		std::cerr << "Got input or output redirection in the middle of pipe. Execution aborted.\n";
		err = 1;
	}
	else if (i == 0 and bcount > 1 and out) {
		std::cerr << "Got output redirection in the beginning of pipe. Execution aborted.\n";
		err = 1;
	}
	else if (i == bcount - 1 and bcount > 1 and in) {
		std::cerr << "Got input redirection at the end of pipe. Execution aborted.\n";
		err = 1;
	}
	return err;
}


void execute(parsed_input *p, BundleControlBlock &bcb) {
	int bcount = p->command.bundle_count;
	int err_sts;
	int fd_in;
	int fd_out;
	std::string str_in;
	std::string capture;
	bool is_last_bundle = false;

	for (int i = 0; i < bcount; i++) {
		if (i == bcount - 1)
			is_last_bundle = true;

		char *pb_name = p->command.bundles[i].name;
		char *in = p->command.bundles[i].input;
		char *out = p->command.bundles[i].output;
		// check if input configuration is OK
		err_sts = sanitize_parameters(i, bcount, in, out);
		if (err_sts)
			return;

		ProcessBundle *pb = bcb.get(pb_name);

		if (!pb) {
			std::cerr << "Unknown bundle: '" << pb_name << "'\n";
			return;
		}

		// Set input redirection
		if (in) 
			fd_in = open(in, O_RDONLY);
		else {
			fd_in = -1;
		}

		// Set output redirection
		if (out) 
			fd_out = open(out, O_WRONLY | O_TRUNC | O_CREAT, 0644);
		else if (!out and is_last_bundle)
			fd_out = STDOUT_FILENO;
		else
			fd_out = -1;

		capture = pb->execute(fd_in, fd_out, str_in);
		str_in = capture;
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
		// Used to prompt markers for inputs and bundle creation
		//if (input_marker) std::cout << ">>> ";
		//else std::cout << "# ";

		std::getline(std::cin >> std::ws, input);

		/*if (input == "ls") {
			for (int i = 0; i < bcb.count(); i++) {
				std::string pb_name = bcb.bundles[i]->name;
				std::cout << "PB name: " << pb_name << std::endl;
			}
			continue;
		}
		if (input == "clear") {
			system("clear");
			continue;
		}*/
		
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
