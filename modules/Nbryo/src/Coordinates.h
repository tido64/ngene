#ifndef COORDINATES
#define COORDINATES

struct Coordinates
{
	const unsigned int directions;	///< Number of directions the cell can "observe"
	int x;							///< The x component of the cell's location
	int y;							///< The y component of the cell's location
	int z;							///< The z component of the cell's location

	Coordinates() : directions(6), x(0), y(0), z(0) { }
	Coordinates(int x, int y, int z) : directions(6), x(x), y(y), z(z) { }

	Coordinates top() const
	{
		return Coordinates(this->x, this->y + 1, this->z);
	}

	Coordinates bottom() const
	{
		return Coordinates(this->x, this->y - 1, this->z);
	}

	Coordinates left() const
	{
		return Coordinates(this->x - 1, this->y, this->z);
	}

	Coordinates right() const
	{
		return Coordinates(this->x + 1, this->y, this->z);
	}

	Coordinates front() const
	{
		return Coordinates(this->x, this->y, this->z + 1);
	}

	Coordinates back() const
	{
		return Coordinates(this->x, this->y, this->z - 1);
	}

	bool operator <(const Coordinates &b) const
	{
		return this->x < b.x;
	}

	bool operator ==(const Coordinates &b) const
	{
		return this->x == b.x && this->y == b.y && this->z == b.z;
	}
};

#endif
