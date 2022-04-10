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
	char buffer[BUFFER_SIZE];

	while (read(fd, buffer, BUFFER_SIZE - 1)) {
		data.append(buffer);
	}
	return data;
}

void ProcessBundle::execute(char *in, char *out) {
	int fd_out;
	int fds[2];
	pipe(fds);
	pid_t sp;

	if (in) {
		std::cout << "input: " << in << std::endl;
		std::ofstream fd_in (in);
	}
	if (out) {
		std::cout << "output: " << out << std::endl;
		fd_out = open(out, O_WRONLY);
	}
	else
		fd_out = fds[1];

	for (int i = 0; i < this->count(); i++) {
		sp = this->subprocess(this->commands[i], fds);
	}

	std::string content = this->readFromFD(fds[0]);
	close(fds[0]);

	// wait for all children
	while (wait(NULL) > 0);
	write(fd_out, content.data(), content.size());
}


pid_t ProcessBundle::subprocess(std::string &cmd, int *fds) {
	pid_t pid = fork();
	if (pid == 0) {
		close(fds[0]); // no reading
		dup2(fds[1], STDOUT_FILENO);
		close(fds[1]);
		char *argv[] = {"/bin/sh", "-c", cmd.data(), NULL};
		execvp(argv[0], argv);
		exit(0);
	}
	close(fds[1]); // no writing
	return pid;
}
