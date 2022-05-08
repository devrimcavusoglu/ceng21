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
	// Notify ready
	hw2_notify(hw2_actions::PROPER_PRIVATE_CREATED, this->id, 0, 0);

	bool should_cont;
	for (int i = 0; i < this->zones.size(); i++) {
		const int x = this->zones[i].first;
		const int y = this->zones[i].second;
		const int n_col = grid[0].size();

		this->lock_area(sem, x, y, n_col);
		should_cont = this->collect_zone(grid, sem, x, y, take_action);
		if (should_cont)
			return;
		this->unlock_area(sem, x, y, n_col);
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
				if (this->obey_command(take_action, sem, x, y, grid[0].size()) == hw2_actions::ORDER_STOP) return false;
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
	take_action.wait(hw2_actions::ORDER_CONTINUE);
	if (take_action.load() == hw2_actions::ORDER_STOP) {
		std::cout << "Im here..\n";
		this->unlock_area(sem, x, y, n_col);
	}
	else if (take_action.load() == hw2_actions::ORDER_BREAK) {
		take_action.wait(hw2_actions::ORDER_BREAK);
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
	hw2_notify(hw2_actions::PROPER_PRIVATE_CLEARED, this->id, 0, 0);
}
