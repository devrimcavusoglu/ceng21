#include "private.hpp"

Private::Private(int id, int x, int y, int t) {
	this->id = id;
	this->collect_time = t;
	this->collect_area = std::make_pair(x,y);
}


void Private::addZone(int x, int y) {
	this->zones.push_back(std::make_pair(x,y));
}

void Private::start_collecting(std::vector<std::vector<int> > &grid, std::vector<std::unique_ptr<std::binary_semaphore>> &sem) {
	for (int i = 0; i < this->zones.size(); i++) {
		this->lock_area(sem, this->zones[i].first, this->zones[i].second, grid[0].size());
		this->collect_zone(grid, this->zones[i].first, this->zones[i].second);
		this->unlock_area(sem, this->zones[i].first, this->zones[i].second, grid[0].size());
	}
}

void Private::collect_zone(std::vector<std::vector<int> > &grid, int x, int y) {
	for (int i = x; i < this->collect_area.first; i++) {
		for (int j = y; j < this->collect_area.second; j++) {
			while (grid[i][j] > 0) {
				Sleep(this->collect_time);
				hw2_notify(hw2_actions::GATHERER_GATHERED, this->id, i, j);
				grid[i][j]--;
				std::cout << "Remaining cigbutts: " << grid[i][j] << std::endl;
			}
		}
	}
}

void Private::lock_area(std::vector<std::unique_ptr<std::binary_semaphore>> &sem, int x, int y, int n_col) {
	for (int i = x; i < this->collect_area.first; i++) {
		for (int j = y; j < this->collect_area.second; j++) 
			sem.at(i*n_col + j)->acquire();
	}
}

void Private::unlock_area(std::vector<std::unique_ptr<std::binary_semaphore>> &sem, int x, int y, int n_col) {
	for (int i = x; i < this->collect_area.first; i++) {
		for (int j = y; j < this->collect_area.second; j++) 
			sem.at(i*n_col + j)->release();
	}
}


void Private::ready() {
	hw2_notify(hw2_actions::GATHERER_CREATED, this->id, 0, 0);
}
