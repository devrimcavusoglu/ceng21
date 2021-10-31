#include <algorithm>
#include <vector>
#include "set.hpp"

bool contains(std::vector<int> container, int value){
	return std::find(container.begin(), container.end(), value) != container.end();
}

Set::Set(){
	*members = new std::vector<int>;
}

Set::Set(std::vector<int> & numbers){
	quickSort(numbers);
	*members = numbers;
}

Set::~Set(){
	delete members;
	delete intersection_members;
}

int Set::size(){
	return members.size();
}

std::vector<int> Set::intersection(Set &other_set){
	std::vector<int> *intersection_members;
	intersection_members = new std::vector<int>{};

	int n_set = other_set.size();

	for (int i{}; i<n_set; i++){
		int value = other_set[i];
		if contains(members, value)
			*intersection_members.push_back(value);
	}

	return *intersection_members;
}


std::vector<int> Set::difference(Set &other_set){
	std::vector<int> *difference_members;
	difference_members = new std::vector<int>{};

	int n = size();

	for (int i{}; i<n; i++){
		int value = members[i];
		if !contains(other_set, value)
			difference_members.push_back(value);
	}

	return *difference_members;
}

void Set::add(int value){
	members.push_back(value);
}
