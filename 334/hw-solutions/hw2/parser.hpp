#ifndef PARSER_HPP
#define PARSER_HPP

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "private.hpp"


enum ParserStatus {
	// INIT
	NONE,

    // Grid
    GRID_CONSTRUCTION_OK,

    // Privates
    PRIVATES_CONSTRUCTION,
    PRIVATES_CONSTRUCTION_OK,
};


class Parser {
public:
	ParserStatus status = ParserStatus::NONE;
	int grid_size[2] = { 0, 0 };
	int n_private = 0;
	std::vector<std::vector<int>> grid;
	std::vector<Private> privates;

	// Parse input
    void parse();

    // Create <x,y> grid
    void createGrid();

    // add Privates
    void addPrivates();
};

#endif //PARSER_HPP