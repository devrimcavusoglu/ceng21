#include "set.cpp"

int main{
	std::vector<int> intersection_members;

	Set mySet;
	mySet.add(1);
	mySet.add(2);
	mySet.add(3);

	set mySet2;
	mySet2.add(3);
	mySet2.add(4);
	mySet2.add(5);


	intersection_members = mySet.intersection(&mySet2);
	

	return 0;
}