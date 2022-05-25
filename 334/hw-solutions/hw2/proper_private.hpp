#ifndef PROPER_PRIVATE_HPP
#define PROPER_PRIVATE_HPP


#include "private.hpp"


class ProperPrivate : public Private {
public:

	ProperPrivate(int id, int x, int y, int t) : Private(id, x, y, t) {};

	void take_break(std::vector<std::unique_ptr<std::binary_semaphore>> &sem);

	void continue_work(
		std::vector<std::vector<int> > &grid, 
		std::vector<std::unique_ptr<std::binary_semaphore>> &sem
	);

	bool is_on_break() {
		return this->on_break;
	}

	virtual void notify_created() override {
		hw2_notify(hw2_actions::PROPER_PRIVATE_CREATED, this->id, 0, 0);
	}

	virtual void notify_arrived(const int x, const int y) override {
		hw2_notify(hw2_actions::PROPER_PRIVATE_ARRIVED, this->id, x, y);
	}

	virtual void notify_action(const int x, const int y) override {
		hw2_notify(hw2_actions::PROPER_PRIVATE_GATHERED, this->id, x, y);
	}

	virtual void notify_action_complete() override {
		hw2_notify(hw2_actions::PROPER_PRIVATE_CLEARED, this->id, 0, 0);
	}

	virtual void notify_exited() override {
		hw2_notify(hw2_actions::PROPER_PRIVATE_EXITED, this->id, 0, 0);
	}

	virtual void notify_stopped() override {
		hw2_notify(hw2_actions::PROPER_PRIVATE_STOPPED, this->id, 0, 0);
	}

	void notify_take_break() {
		hw2_notify(hw2_actions::PROPER_PRIVATE_TOOK_BREAK, this->id, 0, 0);
	}

	void notify_continue() {
		hw2_notify(hw2_actions::PROPER_PRIVATE_CONTINUED, this->id, 0, 0);
	}

	friend std::ostream& operator<<(std::ostream& os, const ProperPrivate& pvt) {
		os << "  ProperPrivate #" << pvt.id  << " | working_area: " << pvt.working_area.first << "x" << pvt.working_area.second << 
			" | working_time: " << pvt.working_time << std::endl;
			for (int j = 0; j < pvt.zones.size(); j++) {
				os << "\tZone " << j << ": (" << pvt.zones[j].first << ", " << pvt.zones[j].second << ")" << std::endl;
			}
		return os;
	}

private:
	bool on_break = false;

	void _start_working(
		std::vector<std::vector<int> > &grid, 
		std::vector<std::unique_ptr<std::binary_semaphore>> &sem,
		int zone_id
	) override;

	// Triggers private to collect cell=(x,y) from the grid.
	bool collect_zone(
		std::vector<std::vector<int> > &grid,
		std::vector<std::unique_ptr<std::binary_semaphore>> &sem, 
		int x, 
		int y
	);
};

#endif //PROPER_PRIVATE_HPP