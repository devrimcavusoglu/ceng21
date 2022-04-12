#include "bundle.h"


#define BUFFER_SIZE 4096


void ProcessBundle::addCommand(std::string &cmd) {
        commands.push_back(cmd);
}

int ProcessBundle::count() const {
	return commands.size();
}

std::vector<std::string> ProcessBundle::getCommands() {
    return commands;
}

std::string ProcessBundle::readFromFD(int fd) {
	std::string data;
	char *buffer = new char[BUFFER_SIZE];
	FILE* f = fdopen(fd, "r");

	while (fgets(buffer, BUFFER_SIZE, f)) {
		data.append(buffer);
	}

	delete [] buffer;
	return data;
}

std::string ProcessBundle::execute(char *in, char *out) {
	
	pid_t sp;
	std::string content;
	std::string input;
	std::string cmd;

	if (in) {
		std::cout << "input: " << in << std::endl;
		int fd_in = open(in, O_RDONLY);
		input = this->readFromFD(fd_in);
	}

	for (int i = 0; i < this->count(); i++) {
		content += this->subprocess(this->commands[i], input);	
	}
	if (out) {
		int fd_out = open(out, O_WRONLY | O_TRUNC | O_CREAT, 0644);
		write(fd_out, content.data(), content.size());
		close(fd_out);
	}
	else {
		std::cout << content;
	}
	// wait for all children
	while (wait(NULL) > 0);
	return content;
}


std::string ProcessBundle::subprocess(std::string &cmd, std::string &input) {
	std::string s;
	int *fds = new int[2];
	pipe(fds);
	pid_t pid = fork();
	if (pid == -1) {
		std::cerr << "Fork failed.";
	}
	if (pid == 0) {
		close(fds[0]); // no reading
		dup2(fds[1], STDOUT_FILENO);
		close(fds[1]);
		system(cmd.data());
		if (input != "") {
			write(STDIN_FILENO, input.data(), input.size());
		}
		exit(0);
	}
	close(fds[1]); // no writing
	s = this->readFromFD(fds[0]);
	close(fds[0]);
	delete [] fds;
	return s;
}
