#include "private.hpp"

Private *private_by_tid(std::vector<Private> &privates, unsigned long tid) {
	for (int i = 0; i < privates.size(); i++) {
		if (privates[i].tid == tid)
			return &privates[i];
	}
	return NULL;
}


Private::Private(int id, int x, int y, int t) {
	this->id = id;
	this->collect_time = t;
	this->collect_area = std::make_pair(x,y);
}


void Private::addZone(int x, int y) {
	this->zones.push_back(std::make_pair(x,y));
}

void Private::start_collecting(
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
			return this->start_collecting(grid, sem);
		}
		this->unlock_area(sem);
		hw2_notify(hw2_actions::PROPER_PRIVATE_CLEARED, this->id, 0, 0);
	}

	// Notify exit
	hw2_notify(hw2_actions::PROPER_PRIVATE_EXITED, this->id, 0, 0);
}

bool Private::collect_zone(
	std::vector<std::vector<int> > &grid,
	std::vector<std::unique_ptr<std::binary_semaphore>> &sem, 
	int x, 
	int y
) {
	for (int i = x; i < x+this->collect_area.first; i++) {
		for (int j = y; j < y+this->collect_area.second; j++) {
			while (grid[i][j] > 0) {
				if (this->current_zone.first == -1)
					return false;
				usleep(this->collect_time * 1000);
				grid[i][j]--;
				hw2_notify(hw2_actions::PROPER_PRIVATE_GATHERED, this->id, i, j);
			}
		}
	}
	return true;
}

void Private::lock_area(
	std::vector<std::unique_ptr<std::binary_semaphore>> &sem, 
	const int x, 
	const int y
) {
	if (this->working())
		return;
	for (int i = x; i < (x+this->collect_area.first); i++) {
		for (int j = y; j < (y+this->collect_area.second); j++) {
			sem.at(i*this->n_col + j)->acquire();
		} 
	}
	this->current_zone = std::make_pair(x, y);
	hw2_notify(hw2_actions::PROPER_PRIVATE_ARRIVED, this->id, x, y);
}

void Private::unlock_area(
	std::vector<std::unique_ptr<std::binary_semaphore>> &sem
) {
	if (!this->working())
		return;
	int x = this->current_zone.first;
	int y = this->current_zone.second;
	for (int i = x; i < x+this->collect_area.first; i++) {
		for (int j = y; j < y+this->collect_area.second; j++) 
			sem.at(i*this->n_col + j)->release();
	}
	this->current_zone = std::make_pair(-1, -1);
}


bool Private::working() {
	if (this->current_zone.first == -1 and this->current_zone.second == -1)
		return false;
	return true;
}
