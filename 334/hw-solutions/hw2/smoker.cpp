#include "smoker.hpp"


void SneakySmoker::addZone(int x, int y, int c) {
	this->zones.push_back(std::make_pair(x,y));
	this->cig_counts.push_back(c);
}
