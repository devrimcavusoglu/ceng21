#include "bundle.h"

void ProcessBundle::addCommand(std::string cmd) {
	this->commands.push_back(cmd);
}

std::vector<char> ProcessBundle::getCommands() {
	return this->commands;
}

void ProcessBundle::execute() {

}
