#include "smoker.hpp"


void SneakySmoker::addZone(int x, int y, int c) {
	this->zones.push_back(std::make_pair(x,y));
	this->cig_counts.push_back(c);
}


void SneakySmoker::_start_working(
	std::vector<std::vector<int> > &grid, 
	std::vector<std::unique_ptr<std::binary_semaphore>> &sem
) {
	this->tid = pthread_self();
	this->n_col = grid[0].size();
	bool area_cleared;
	for (int i = 0; i < this->zones.size(); i++) {
		// get top-left (x,y)
		const int x = this->zones[i].first - 1;
		const int y = this->zones[i].second - 1;
		const int c = this->cig_counts[i];

		this->lock_area(sem, x, y);
		hw2_notify(hw2_actions::SNEAKY_SMOKER_ARRIVED, this->id, x+1, y+1);
		area_cleared = this->litter_zone(grid, sem, x, y, c);
		if (!area_cleared) {
			return this->_start_working(grid, sem);
		}
		this->unlock_area(sem);
		hw2_notify(hw2_actions::SNEAKY_SMOKER_LEFT, this->id, 0, 0);
	}

	// Notify exit
	hw2_notify(hw2_actions::SNEAKY_SMOKER_EXITED, this->id, 0, 0);
}


bool SneakySmoker::litter_zone(
	std::vector<std::vector<int> > &grid,
	std::vector<std::unique_ptr<std::binary_semaphore>> &sem, 
	int x, 
	int y,
	int c
) {
	std::pair<int, int> cell;

	int iter = 0;
	while (c > 0) {
		if (!this->is_working())
			return false;
		cell = this->get_next_cell(iter, x, y);
		iter++;
		usleep(this->working_time * 1000);
		grid[cell.first][cell.second]++;
		c--;
		hw2_notify(hw2_actions::SNEAKY_SMOKER_FLICKED, this->id, cell.first, cell.second);
	}
	return true;
}


std::pair<int, int> SneakySmoker::get_next_cell(int iter, const int x, const int y) {
	std::pair<int, int> cell_vals = this->littering_cells[iter % this->littering_cells.size()];
	return std::make_pair(cell_vals.first + x, cell_vals.second + y);
}
