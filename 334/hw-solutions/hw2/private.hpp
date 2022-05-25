#ifndef PRIVATE_HPP
#define PRIVATE_HPP

#include <atomic>
#include <iostream>
#include <memory>
#include <ostream>
#include <semaphore>
#include <vector>
#include <unistd.h>
#include <utility>

#include "hw2_output.h"


class Private {
public:
	int id;
	int n_col;
	unsigned int working_time;
	unsigned long tid = 0;
	std::vector<std::pair<int, int>> zones;
	std::pair<int, int> working_area;
	std::pair<int, int> current_zone = std::make_pair(-1, -1);

	Private(int id, int x, int y, int t);

	void start_working(
		std::vector<std::vector<int> > &grid, 
		std::vector<std::unique_ptr<std::binary_semaphore>> &sem
	) {
		this->tid = pthread_self();
		this->n_col = grid[0].size();
		for (int i = 0; i < this->zones.size(); i++) {
			this->_start_working(grid, sem, i);
			if (this->is_stopped())
				return;
		}
		this->notify_exited();
	}

	// Add left corner cell of duty zone for private.
	void addZone(int x, int y);

	// Actually we need to check for intersection for locks & unlocks to
	// better utilize collection of cigbutts.
	// E.g G0(0,0), G1(1,1), G2(2,2) all collect 2x2, in this scenario
	// G0 and G2 should be able to collect together without waiting each other,
	// but current implementation locks/unlocks cells, so G1 can lock and 
	// interrupt G2 while G0 is already collecting.
	void lock_area(
		std::vector<std::unique_ptr<std::binary_semaphore>> &sem, 
		const int x, 
		const int y
	);

	void unlock_area(
		std::vector<std::unique_ptr<std::binary_semaphore>> &sem 
	);

	void set_mutex();

	bool is_working();

	bool is_waiting();

	bool is_stopped();

	void stop(std::vector<std::unique_ptr<std::binary_semaphore>> &sem);

	void lock_mutex() {
		pthread_mutex_lock(&this->mutex);
	}

	void unlock_mutex() {
		pthread_mutex_unlock(&this->mutex);
	}

	virtual void notify_created() {}

	virtual void notify_arrived(const int x, const int y) {}

	virtual void notify_action(const int x, const int y) {}

	virtual void notify_action_complete() {}

	virtual void notify_exited() {}

	virtual void notify_stopped() {}

private:
	bool waiting_to_lock = false;
	bool stopped = false;

	// this mutex is reserved for the thread for any 
	// potential use for private works. May or may not 
	// be used.
	pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

	// Internal worker method called by `start_working`. 
	// This method must be overridden in child class.
	virtual void _start_working(
		std::vector<std::vector<int> > &grid, 
		std::vector<std::unique_ptr<std::binary_semaphore>> &sem,
		int zone_id
	) {}
};

template <class T>
T *private_by_tid(std::vector<T> &privates, unsigned long tid) {
	for (int i = 0; i < privates.size(); i++) {
		if (privates[i].tid == tid)
			return &privates[i];
	}
	return NULL;
}

#endif //PRIVATE_HPP