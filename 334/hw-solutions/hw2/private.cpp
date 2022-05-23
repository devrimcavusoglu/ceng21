#include "private.hpp"


Private::Private(int id, int x, int y, int t) {
	this->id = id;
	this->working_time = t;
	this->working_area = std::make_pair(x,y);
}


void Private::addZone(int x, int y) {
	this->zones.push_back(std::make_pair(x,y));
}


void Private::lock_area(
	std::vector<std::unique_ptr<std::binary_semaphore>> &sem, 
	const int x, 
	const int y
) {
	if (this->is_working())
		return;
	else
		this->waiting_to_lock = true;
	for (int i = x; i < (x+this->working_area.first); i++) {
		for (int j = y; j < (y+this->working_area.second); j++) {
			sem.at(i*this->n_col + j)->acquire();
		} 
	}
	this->waiting_to_lock = false;
	this->current_zone = std::make_pair(x, y);
}

void Private::unlock_area(
	std::vector<std::unique_ptr<std::binary_semaphore>> &sem
) {
	if (!this->is_working())
		return;
	int x = this->current_zone.first;
	int y = this->current_zone.second;
	for (int i = x; i < x+this->working_area.first; i++) {
		for (int j = y; j < y+this->working_area.second; j++) 
			sem.at(i*this->n_col + j)->release();
	}
	this->current_zone = std::make_pair(-1, -1);
}


bool Private::is_working() {
	if (this->current_zone.first == -1 and this->current_zone.second == -1)
		return false;
	return true;
}


bool Private::is_waiting() {
	return this->waiting_to_lock;
}


bool Private::is_stopped() {
	return this->stopped;
}


void Private::stop(std::vector<std::unique_ptr<std::binary_semaphore>> &sem) {
	this->stopped = true;
	this->unlock_area(sem);
	this->notify_stopped();
	pthread_exit(NULL);
}


