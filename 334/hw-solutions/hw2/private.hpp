#ifndef PRIVATE_HPP
#define PRIVATE_HPP

#include <iostream>
#include <memory>
#include <ostream>
#include <semaphore>
#include <vector>
#include <unistd.h>
#include <utility>
#include <windows.h>

#include "hw2_output.h"


class Private {
public:
	std::vector<std::pair<int, int>> zones;
	int id;
	std::pair<int, int> collect_area;
	int collect_time;

	// Constructor for private
	Private(int id, int x, int y, int t);

	// Add left corner cell of duty zone for private.
	void addZone(int x, int y);

	// Private starts collecting zones one-by-one
	void start_collecting(std::vector<std::vector<int> > &grid, std::vector<std::unique_ptr<std::binary_semaphore>> &sem);

	// Triggers private to collect cell=(x,y) from the grid.
	void collect_zone(std::vector<std::vector<int> > &grid, int x, int y);

	// notify ready
	void ready();

	void lock_area(std::vector<std::unique_ptr<std::binary_semaphore>> &sem, int x, int y, int n_col);

	void unlock_area(std::vector<std::unique_ptr<std::binary_semaphore>> &sem, int x, int y, int n_col);

	friend std::ostream& operator<<(std::ostream& os, const Private& pvt) {
		os << "  Private #" << pvt.id  << " | collect_area: " << pvt.collect_area.first << "x" << pvt.collect_area.first << 
			" | collect_time: " << pvt.collect_time << std::endl;
			for (int j = 0; j < pvt.zones.size(); j++) {
				os << "\tZone " << j << ": (" << pvt.zones[j].first << ", " << pvt.zones[j].second << ")" << std::endl;
			}
		return os;
	}
};

#endif //PRIVATE_HPP