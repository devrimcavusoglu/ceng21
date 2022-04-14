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

std::string ProcessBundle::execute(int fd_in, int fd_out, std::string &str_in) {
	pid_t sp;
	std::string content;
	std::string input;
	redirection_t redirections;

	if (fd_in != -1) {
		input = this->readFromFD(fd_in);
		close(fd_in);
	}
	if (!str_in.empty())
		input = str_in;

	//std::cout << "call with in: " << fd_in	<< " out: " << fd_out << std::endl;
	for (int i = 0; i < this->count(); i++) {
		redirections = this->subprocess(this->commands[i]);
		dprintf(redirections.stdin.second, "%s", input.data());
		close(redirections.stdin.second);
		content += this->readFromFD(redirections.stdout.first);
		close(redirections.stdout.first);
	}

	if (fd_out == STDOUT_FILENO) {
		std::cout << content;
	}
	else if (fd_out != -1) {
		write(fd_out, content.data(), content.size());
		close(fd_out);	
	}
	// wait for all children
	while (wait(NULL) > 0);
	return content;
}


redirection_t ProcessBundle::subprocess(std::string &cmd) {
	std::string s;
	int fds_in[2];
	int fds_out[2];
	pipe(fds_in); //pipe for input redirection
	pipe(fds_out); //pipe for output redirection

	redirection_t redir = { 
		std::make_pair(fds_in[0], fds_in[1]), 
		std::make_pair(fds_out[0], fds_out[1]) 
	};
	pid_t pid = fork();
	if (pid == -1) {
		std::cerr << "Fork failed.";
	}
	if (pid == 0) {
		close(redir.stdin.second);
		close(redir.stdout.first);
		dup2(redir.stdout.second, STDOUT_FILENO);
		dup2(redir.stdin.first, STDIN_FILENO);
		close(redir.stdout.second);
		close(redir.stdin.first);
		system(cmd.data());
		exit(0);
	}
	close(redir.stdin.first);
	close(redir.stdout.second);
	return redir;
}
