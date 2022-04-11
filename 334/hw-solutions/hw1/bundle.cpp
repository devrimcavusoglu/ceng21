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

	while (read(fd, buffer, BUFFER_SIZE)) {
		data.append(buffer);
	}

	delete [] buffer;
	return data;
}

void ProcessBundle::execute(char *in, char *out) {
	int *fds = new int[2];
	pipe(fds);
	pid_t sp;

	if (in) {
		std::cout << "input: " << in << std::endl;
		std::ifstream fd_in (in);
	}

	for (int i = 0; i < this->count(); i++) {
		sp = this->subprocess(this->commands[i], fds);
	}
	
	std::string content = this->readFromFD(fds[0]);
	close(fds[0]);
	if (out) {
		std::cout << "output: " << out << std::endl;
		std::ofstream myfile;
		myfile.open(out);
		myfile << content;
		myfile.close();
		//fd_out = open(out, O_WRONLY | O_APPEND | O_CREAT, 0644);
		//write(fd_out, content.data(), content.size());
		//close(fd_out);
	}
	else {
		/*std::cout << "read size: " << content.size() << std::endl;
		std::cout << "content ---->\n" << content;*/
		std::cout << content;
	}
	// wait for all children
	while (wait(NULL) > 0);
	delete [] fds;
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
