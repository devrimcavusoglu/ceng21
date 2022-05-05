
class Box {
public:
	Box(int x, int y, int width, int height) {
		this->x = x;
		this->y = y;
		this->width = width;
		this->height = height;
	}

	// checks whether there is intersection
	bool intersects(Box &other) const {
		int smallest_x, smallest_y;
		if other
	}

private:
	int x;
	int y;
	int width;
	int height;
};
