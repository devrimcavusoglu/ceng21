#ifndef SMOKER_HPP
#define SMOKER_HPP

#include "private.hpp"


class SneakySmoker : public Private {
public:
	std::vector<int> cig_counts;

	// Constructor for sneaky-smoker
	SneakySmoker(int id, int t) : Private(id, 3, 3, t) {};

	// Add left corner cell of duty zone for private.
	void addZone(int x, int y, int c);

	virtual void notify_created() override {
		hw2_notify(hw2_actions::SNEAKY_SMOKER_CREATED, this->id, 0, 0);
	}

	virtual void notify_arrived(const int x, const int y) override {
		hw2_notify(hw2_actions::SNEAKY_SMOKER_ARRIVED, this->id, x, y);
	}

	virtual void notify_action(const int x, const int y) override {
		hw2_notify(hw2_actions::SNEAKY_SMOKER_FLICKED, this->id, x, y);
	}

	virtual void notify_action_complete() override {
		hw2_notify(hw2_actions::SNEAKY_SMOKER_LEFT, this->id, 0, 0);
	}

	virtual void notify_exited() override {
		hw2_notify(hw2_actions::SNEAKY_SMOKER_EXITED, this->id, 0, 0);
	}

	virtual void notify_stopped() override {
		hw2_notify(hw2_actions::SNEAKY_SMOKER_STOPPED, this->id, 0, 0);
	}

	friend std::ostream& operator<<(std::ostream& os, const SneakySmoker& pvt) {
		os << "  SneakySmoker #" << pvt.id  << " | working_area: " << pvt.working_area.first << "x" << pvt.working_area.second << 
			" | working_time: " << pvt.working_time << std::endl;
			for (int j = 0; j < pvt.zones.size(); j++) {
				os << "\tZone " << j << ": (" << pvt.zones[j].first << ", " << pvt.zones[j].second << ")" 
					" cig_count: " << pvt.cig_counts[j] << std::endl;
			}
		return os;
	}

private:
	std::vector<std::pair<int, int>> littering_cells = {
		std::make_pair(0,0),
		std::make_pair(0,1),
		std::make_pair(0,2),
		std::make_pair(1,2),
		std::make_pair(2,2),
		std::make_pair(2,1),
		std::make_pair(2,0),
		std::make_pair(1,0)
	};

	void _start_working(
		std::vector<std::vector<int> > &grid, 
		std::vector<std::unique_ptr<std::binary_semaphore>> &sem
	) override;

	// Triggers private to collect cell=(x,y) from the grid.
	bool litter_zone(
		std::vector<std::vector<int> > &grid,
		std::vector<std::unique_ptr<std::binary_semaphore>> &sem, 
		int x, 
		int y,
		int c
	);

	std::pair<int, int> get_next_cell(int iter, const int x, const int y);
};

#endif //SMOKER_HPP