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


int main() {
	std::string input;
 	parsed_input *p;
 	int sts;

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
				std::string input_bundle;
				while (true) {
					std::cin >> input_bundle;
					char c_char[input_bundle.length() + 1];
					strcpy(c_char, input_bundle.c_str());
					/*std::cout << "Recieved: '" << c_char << "'\n";*/
					sts = parse(c_char, 1, p);
					if (input_bundle == "pbs") {
						sts = parse(c_char, 0, p);
						std::string s;
						s = p->command.bundle_name;
						std::cout << s << std::endl;
						break;
					}
					else {
						sts = parse(c_char, 1, p);
					}
				}
			}
			else {
				std::cout << "Unknown cmd.\n";
			}
		}
	}
}
