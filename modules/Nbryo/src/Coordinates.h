#ifndef COORDINATES
#define COORDINATES

struct Coordinates
{
	int x;
	int y;
	int z;

	Coordinates() : x(0), y(0), z(0) { }
	Coordinates(int x, int y, int z) : x(x), y(y), z(z) { }

	Coordinates top() const { return Coordinates(this->x, this->y + 1, this->z); }

	Coordinates bottom() const { return Coordinates(this->x, this->y - 1, this->z); }

	Coordinates left() const { return Coordinates(this->x - 1, this->y, this->z); }

	Coordinates right() const { return Coordinates(this->x + 1, this->y, this->z); }

	Coordinates front() const { return Coordinates(this->x, this->y, this->z + 1); }

	Coordinates back() const { return Coordinates(this->x, this->y, this->z - 1); }

	bool operator <(const Coordinates &b) const
	{
		return this->x < b.x;
	}
};

#endif
