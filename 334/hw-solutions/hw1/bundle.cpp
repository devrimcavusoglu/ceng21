#include "bundle.h"


void ProcessBundle::addCommand(std::string &cmd) {
        commands.push_back(cmd);
}

int ProcessBundle::count() const {
	return commands.size();
}

std::vector<std::string> ProcessBundle::getCommands() {
    return commands;
}

void ProcessBundle::execute(char *in, char *out) {
	if (in) {
		std::cout << "input: " << in << std::endl;
		std::ofstream fd_in (in);
	}
	if (out) {
		std::cout << "output: " << out << std::endl;
		std::ofstream fd_out (out, ios::out | ios::app);
	}

	int pid;

	for (int i = 0; i < this->count(); i++) {
		pid = fork();
		if (pid == 0) {
			char *cmd[] = {"/bin/sh", "-c", this->commands[i].data(), NULL};
			execvp(cmd[0], cmd);
		}
	}

	waitpid(pid, NULL, 0);
}
