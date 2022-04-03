#include "bcb.h"

void ProcessBundle::add(ProcessBundle pb) {
	this->bundles.push_back(&pb)
}

std::vector<ProcessBundle*> ProcessBundle::all() {
	return this->bundles;
}
