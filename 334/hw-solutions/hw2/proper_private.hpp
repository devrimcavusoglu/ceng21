#ifndef PROPER_PRIVATE_HPP
#define PROPER_PRIVATE_HPP

#include "private.hpp"


class ProperPrivate : public Private {
public:

	ProperPrivate(int id, int x, int y, int t) : Private(id, x, y, t) {};

	// ProperPrivate starts collecting zones one-by-one
	void start_collecting(
		std::vector<std::vector<int> > &grid, 
		std::vector<std::unique_ptr<std::binary_semaphore>> &sem
	);

	// Triggers private to collect cell=(x,y) from the grid.
	bool collect_zone(
		std::vector<std::vector<int> > &grid,
		std::vector<std::unique_ptr<std::binary_semaphore>> &sem, 
		int x, 
		int y
	);

	friend std::ostream& operator<<(std::ostream& os, const ProperPrivate& pvt) {
		os << "  ProperPrivate #" << pvt.id  << " | working_area: " << pvt.working_area.first << "x" << pvt.working_area.second << 
			" | working_time: " << pvt.working_time << std::endl;
			for (int j = 0; j < pvt.zones.size(); j++) {
				os << "\tZone " << j << ": (" << pvt.zones[j].first << ", " << pvt.zones[j].second << ")" << std::endl;
			}
		return os;
	}
};

#endif //PROPER_PRIVATE_HPP