#include "private.hpp"

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
	std::vector<std::unique_ptr<std::binary_semaphore>> &sem,
	std::atomic<hw2_actions> &take_action
) {
	bool area_cleared;
	for (int i = 0; i < this->zones.size(); i++) {
		const int x = this->zones[i].first;
		const int y = this->zones[i].second;
		const int n_col = grid[0].size();

		this->lock_area(sem, x, y, n_col);
		area_cleared = this->collect_zone(grid, sem, x, y, take_action);
		if (!area_cleared) {
			take_action.wait(hw2_actions::ORDER_BREAK);
			if (take_action.load() == hw2_actions::ORDER_CONTINUE) {
				hw2_notify(hw2_actions::PROPER_PRIVATE_CONTINUED, this->id, 0, 0);
				return this->start_collecting(grid, sem, take_action);
			}
			else // stop cmd
				return;
		}
		this->unlock_area(sem, x, y, n_col);
		hw2_notify(hw2_actions::PROPER_PRIVATE_CLEARED, this->id, 0, 0);
	}

	// Notify exit
	hw2_notify(hw2_actions::PROPER_PRIVATE_EXITED, this->id, 0, 0);
}

bool Private::collect_zone(
	std::vector<std::vector<int> > &grid,
	std::vector<std::unique_ptr<std::binary_semaphore>> &sem, 
	int x, 
	int y,
	std::atomic<hw2_actions> &take_action
) {
	for (int i = x; i < x+this->collect_area.first; i++) {
		for (int j = y; j < y+this->collect_area.second; j++) {
			while (grid[i][j] > 0) {
				hw2_actions action_state = this->obey_command(take_action, sem, x, y, grid[0].size()); 
				if (action_state == hw2_actions::ORDER_STOP or action_state == hw2_actions::ORDER_BREAK) 
					return false;
				Sleep(this->collect_time);
				grid[i][j]--;
				hw2_notify(hw2_actions::PROPER_PRIVATE_GATHERED, this->id, i, j);
			}
		}
	}
	return true;
}

hw2_actions Private::obey_command(
	std::atomic<hw2_actions> &take_action,
	std::vector<std::unique_ptr<std::binary_semaphore>> &sem, 
	const int x, 
	const int y, 
	const int n_col
) {
	if (take_action.load() == hw2_actions::ORDER_STOP) {
		hw2_notify(hw2_actions::PROPER_PRIVATE_STOPPED, this->id, 0, 0);
		this->unlock_area(sem, x, y, n_col);
	}
	if (take_action.load() == hw2_actions::ORDER_BREAK) {
		hw2_notify(hw2_actions::PROPER_PRIVATE_TOOK_BREAK, this->id, 0, 0);
		this->unlock_area(sem, x, y, n_col);
	}
	return take_action.load();
}

void Private::lock_area(
	std::vector<std::unique_ptr<std::binary_semaphore>> &sem, 
	const int x, 
	const int y, 
	const int n_col
) {
	for (int i = x; i < (x+this->collect_area.first); i++) {
		for (int j = y; j < (y+this->collect_area.second); j++) {
			sem.at(i*n_col + j)->acquire();
		} 
	}
	hw2_notify(hw2_actions::PROPER_PRIVATE_ARRIVED, this->id, x, y);
}

void Private::unlock_area(
	std::vector<std::unique_ptr<std::binary_semaphore>> &sem, 
	const int x, 
	const int y,
	const int n_col
) {
	for (int i = x; i < x+this->collect_area.first; i++) {
		for (int j = y; j < y+this->collect_area.second; j++) 
			sem.at(i*n_col + j)->release();
	}
}
