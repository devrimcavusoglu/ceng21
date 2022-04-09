#include <iostream>
#include <string>
#include <sys/wait.h>
#include <sys/types.h>
#include "unistd.h"

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

void ProcessBundle::execute(int in, int out) {
	for (int i = 0; i < this->count(); i++) {
		std::cout << "current command: " << this->commands[i] << std::endl;
		int pid = fork();
		if (pid == 0) {
			char *cmd[] = {"/bin/sh", "-c", this->commands[0].data(), NULL};
			execvp(cmd[0], cmd);
		}
		int status;
		waitpid(pid, NULL, 0);
	}
}
