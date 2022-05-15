#include "proper_private.hpp"


void ProperPrivate::_start_working(
	std::vector<std::vector<int> > &grid, 
	std::vector<std::unique_ptr<std::binary_semaphore>> &sem
) {
	this->tid = pthread_self();
	this->n_col = grid[0].size();
	bool area_cleared;
	for (int i = 0; i < this->zones.size(); i++) {
		const int x = this->zones[i].first;
		const int y = this->zones[i].second;

		this->lock_area(sem, x, y);
		area_cleared = this->collect_zone(grid, sem, x, y);
		if (!area_cleared) {
			return this->_start_working(grid, sem);
		}
		this->unlock_area(sem);
		hw2_notify(hw2_actions::PROPER_PRIVATE_CLEARED, this->id, 0, 0);
	}

	// Notify exit
	hw2_notify(hw2_actions::PROPER_PRIVATE_EXITED, this->id, 0, 0);
}

// Triggers private to collect cell=(x,y) from the grid.
bool ProperPrivate::collect_zone(
	std::vector<std::vector<int> > &grid,
	std::vector<std::unique_ptr<std::binary_semaphore>> &sem, 
	int x, 
	int y
) {
	for (int i = x; i < x+this->working_area.first; i++) {
		for (int j = y; j < y+this->working_area.second; j++) {
			while (grid[i][j] > 0) {
				if (!this->is_working())
					return false;
				usleep(this->working_time * 1000);
				grid[i][j]--;
				hw2_notify(hw2_actions::PROPER_PRIVATE_GATHERED, this->id, i, j);
			}
		}
	}
	return true;
}