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

	friend std::ostream& operator<<(std::ostream& os, const SneakySmoker& pvt) {
		os << "  SneakySmoker #" << pvt.id  << " | working_area: " << pvt.working_area.first << "x" << pvt.working_area.second << 
			" | working_time: " << pvt.working_time << std::endl;
			for (int j = 0; j < pvt.zones.size(); j++) {
				os << "\tZone " << j << ": (" << pvt.zones[j].first << ", " << pvt.zones[j].second << ")" 
					" cig_count: " << pvt.cig_counts[j] << std::endl;
			}
		return os;
	}
};

#endif //SMOKER_HPP