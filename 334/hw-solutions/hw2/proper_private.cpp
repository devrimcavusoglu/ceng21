#include "proper_private.hpp"


void ProperPrivate::_start_working(
	std::vector<std::vector<int> > &grid, 
	std::vector<std::unique_ptr<std::binary_semaphore>> &sem
) {
	this->tid = pthread_self();
	this->n_col = grid[0].size();
	bool area_cleared;
	for (int i = 0; i < this->zones.size(); i++) {
		if (this->is_stopped())
			return;
		const int x = this->zones[i].first;
		const int y = this->zones[i].second;

		this->lock_area(sem, x, y);
		this->notify_arrived(x, y);
		area_cleared = this->collect_zone(grid, sem, x, y);
		if (!area_cleared) {
			return this->_start_working(grid, sem);
		}
		this->unlock_area(sem);
		this->notify_action_complete();
	}

	// Notify exit
	this->notify_exited();
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
				for (int k = 0; k < 100; k++) {
					// Rather than sleeping the whole working time
					// splitting the working time into small chunks 
					// like this allows the thread to response (almost) on point.
					if (!this->is_working())
						return false; 
					usleep(this->working_time * 10);
				}
				grid[i][j]--;
				this->notify_action(i, j);
			}
		}
	}
	return true;
}