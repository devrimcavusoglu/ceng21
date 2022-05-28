#ifndef PARSER_HPP
#define PARSER_HPP

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "proper_private.hpp"
#include "smoker.hpp"


enum ParserStatus {
	// Init Status
	NONE,

    // Grid
    GRID_CONSTRUCTION_OK,

    // ProperPrivates
    PRIVATES_CONSTRUCTION,
    PRIVATES_CONSTRUCTION_OK,

    // Commands
    COMMANDS_CONSTRUCTION,
    COMMANDS_CONSTRUCTION_OK,

    // Sneaky Smokers
	SNEAKY_SMOKER_CONSTRUCTION,
    SNEAKY_SMOKER_CONSTRUCTION_OK    
};


typedef struct Command {
	unsigned int notify_time;
	enum hw2_actions action;
} command_t;


class Parser {
public:
	ParserStatus status = ParserStatus::NONE;
	int grid_size[2] = { 0, 0 };
	int n_privates = 0;
	int n_commands = 0;
    int n_smokers = 0;
	std::vector<std::vector<int>> grid;
	std::vector<ProperPrivate> privates;
	std::vector<Command> commands;
	std::vector<SneakySmoker> sneaky_smokers;

	// Parse input
    void parse();

    // Create <x,y> grid
    void createGrid();

    // add ProperPrivates
    void addProperPrivates();

    // add Commands (part-2)
    void addCommands();

    // add SneakySmokers (part-3)
    void addSneakySmokers();
};

#endif //PARSER_HPP