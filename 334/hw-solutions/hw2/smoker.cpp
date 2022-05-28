#include "smoker.hpp"


void SneakySmoker::addZone(int x, int y, int c) {
	this->zones.push_back(std::make_pair(x,y));
	this->cig_counts.push_back(c);
}


void SneakySmoker::_start_working(
	std::vector<std::vector<int> > &grid, 
	std::vector<std::unique_ptr<std::binary_semaphore>> &sem,
	int zone_id
) {
	bool area_cleared;
	// get top-left (x,y)
	const int x = this->zones[zone_id].first - 1;
	const int y = this->zones[zone_id].second - 1;
	const int c = this->cig_counts[zone_id];

	this->lock_area(sem, x, y);
	this->notify_arrived(x+1, y+1);
	area_cleared = this->litter_zone(grid, sem, x, y, c);
	if (this->is_stopped())
		return;
	if (!area_cleared) {
		return this->_start_working(grid, sem, zone_id);
	}
	this->unlock_area(sem);
	this->notify_action_complete();
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
		cell = this->get_next_cell(iter, x, y);
		iter++;
		for (int t = 0; t < 200; t++) {
			usleep(this->working_time * 5);
			if (this->is_stopped())
				return false;
		}
		grid[cell.first][cell.second]++;
		c--;
		this->notify_action(cell.first, cell.second);
	}
	return true;
}


std::pair<int, int> SneakySmoker::get_next_cell(int iter, const int x, const int y) {
	std::pair<int, int> cell_vals = this->littering_cells[iter % this->littering_cells.size()];
	return std::make_pair(cell_vals.first + x, cell_vals.second + y);
}
