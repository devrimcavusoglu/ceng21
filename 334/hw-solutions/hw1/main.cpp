#include <cstdio>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <array>

#include "parser.c"


std::string exec(const char* cmd) {
    std::array<char, 128> buffer;
    std::string result;
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
    if (!pipe) {
        throw std::runtime_error("popen() failed!");
    }
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    return result;
}


char *str_to_char(const std::string& str) {
	char c_char[str.length() + 1];
	strcpy(c_char, str.c_str());
	return c_char;
}


void parse_input(char *init_line) {
	int sts;
	parsed_input *p;
	std::string input_bundle;

	sts = parse(init_line, 1, p);
	do {
		std::cin >> input_bundle;
		char *c_char = str_to_char(input_bundle);
		std::cout << c_char << std::endl;
		sts = parse(c_char, 1, p);
		/*s = p->command.bundle_name;*/
		std::cout << sts << std::endl;
	} while (sts != 1);
}


int main() {
	std::string input;

	while (true) {
		std::cout << ">>";
		std::cin >> input;
		
		if(input=="quit")
			return 0;
		else if (input == "test") {
			std::string res = exec("echo abc");
			std::cout << res;
		}
		else {		
			if (input.rfind("pbc", 0) == 0) {
				char *init_line = str_to_char(input);
				parse_input(init_line);
			}
			else {
				std::cout << "Unknown cmd.\n";
			}
		}
	}
}
