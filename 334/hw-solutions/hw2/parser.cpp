#include "parser.hpp"


void Parser::parse() {
	std::string buffer;

	while (std::getline(std::cin, buffer)) {
		std::istringstream iss(buffer);
		if (status == ParserStatus::NONE) {
			iss >> this->grid_size[0] >> this->grid_size[1];
			this->createGrid();
			this->status = ParserStatus::GRID_CONSTRUCTION_OK;
		}
		else if (status == ParserStatus::GRID_CONSTRUCTION_OK) {
			this->status = ParserStatus::PRIVATES_CONSTRUCTION;
			continue;
		}
		else if (status == ParserStatus::PRIVATES_CONSTRUCTION) {
			iss >> this->n_privates;
			this->addPrivates();
			this->status = ParserStatus::PRIVATES_CONSTRUCTION_OK;
		}
		else if (status == ParserStatus::PRIVATES_CONSTRUCTION_OK) {
			this->status = ParserStatus::COMMANDS_CONSTRUCTION;
			continue;
		}
		else if (status == ParserStatus::COMMANDS_CONSTRUCTION) {
			iss >> this->n_commands;
			this->addCommands();
			this->status = ParserStatus::COMMANDS_CONSTRUCTION_OK;
		}
		else {
			break;
		}
	}
}


void Parser::createGrid() {
	int val;
	for (int i = 0; i < this->grid_size[0]; i++) {
		std::vector<int> grid_row;
		for (int j = 0; j < this->grid_size[1]; j++) {
			std::cin >> val;
			grid_row.push_back(val);
		}
		this->grid.push_back(grid_row);
	}
}


void Parser::addPrivates() {
	int id, x, y, t, n_zones;
	int z_x, z_y;
	for (int i = 0; i < this->n_privates; i++) {
		std::cin >> id >> x >> y >> t >> n_zones;
		Private p(id, x, y, t);
		for (int j = 0; j < n_zones; j++) {
			std::cin >> z_x >> z_y;
			p.addZone(z_x, z_y);
		}
		this->privates.push_back(p);
	}
}


void Parser::addCommands() {
	unsigned int t;
	std::string action;
	for (int i = 0; i < this->n_commands; i++) {
		command_t cmd;
		std::cin >> t >> action;
		cmd.notify_time = t;
		if (action == "break")
			cmd.action = hw2_actions::ORDER_BREAK;
		else if (action == "continue")
			cmd.action = hw2_actions::ORDER_CONTINUE;
		else if (action == "stop")
			cmd.action = hw2_actions::ORDER_STOP;
		this->commands.push_back(cmd);
	}
}
