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
		if (this->is_stopped())
			return;
		else if (!area_cleared) {
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
				for (int k = 0; k < 500; k++) {
					// Rather than sleeping the whole working time
					// splitting the working time into small chunks 
					// like this allows the thread to response (almost) on point.
					usleep(this->working_time * 2);
					if (this->is_stopped() or this->is_on_break())
						return false; 
				}
				grid[i][j]--;
				this->notify_action(i, j);
			}
		}
	}
	return true;
}

void ProperPrivate::take_break(std::vector<std::unique_ptr<std::binary_semaphore>> &sem) {
	if (this->is_on_break())
		return;
	this->unlock_area(sem);
	this->on_break = true;
	this->notify_take_break();
}

void ProperPrivate::continue_work(
	std::vector<std::vector<int> > &grid, 
	std::vector<std::unique_ptr<std::binary_semaphore>> &sem
) {
	if (!this->is_on_break())
		return;
	this->on_break = false;
	this->notify_continue();
}