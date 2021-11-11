#include "ostream"

std::ostream& operator<<(std::ostream& out, Box& other);

class Box{
private:
	int l; // length
	int b; // breadth
	int h; // depth
public:
	Box();
	Box(int length, int breadth, int height);
	Box(const Box& other);
	int getLength();
	int getBreadth();
	int getHeight();
	long long CalculateVolume();
	bool operator<(Box& other);
	friend std::ostream& operator<<(std::ostream& out, Box& other);
};
