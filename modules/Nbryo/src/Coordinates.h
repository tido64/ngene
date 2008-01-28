#ifndef COORDINATES
#define COORDINATES

#include "Direction.h"

struct Coordinates
{
	const unsigned int directions;	///< Number of directions the cell can "observe"
	int x;							///< The x component of the cell's location
	int y;							///< The y component of the cell's location
	int z;							///< The z component of the cell's location

	Coordinates() : directions(6), x(0), y(0), z(0) { }
	Coordinates(int x, int y, int z) : directions(6), x(x), y(y), z(z) { }

	Coordinates look(Direction::direction d) const
	{
		switch (d)
		{
			case Direction::top:
				return Coordinates(this->x, this->y + 1, this->z);
				break;
			case Direction::bottom:
				return Coordinates(this->x, this->y - 1, this->z);
				break;
			case Direction::left:
				return Coordinates(this->x - 1, this->y, this->z);
				break;
			case Direction::right:
				return Coordinates(this->x + 1, this->y, this->z);
				break;
			case Direction::front:
				return Coordinates(this->x, this->y, this->z + 1);
				break;
			case Direction::back:
				return Coordinates(this->x, this->y, this->z - 1);
				break;
			default:
				return Coordinates(this->x, this->y, this->z);
				break;
		}
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
