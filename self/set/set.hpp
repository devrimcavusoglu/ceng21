
class Set
{
private:
	std::vector<int> *members;
public:
	Set();
	~Set();
	std::vector<int> intersection(Set &other_set);
	std::vector<int> difference(Set &other_set);
	int size();
	void add(int value);
};
