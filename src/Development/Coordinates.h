#ifndef COORDINATES
#define COORDINATES

#include "Direction.h"

class Coordinates
{
public:
	int x,	///< The x component of a cell's location
		y,	///< The y component of a cell's location
		z;	///< The z component of a cell's location

	Coordinates::Coordinates() : x(0), y(0), z(0) { }
	Coordinates::Coordinates(const Coordinates &c) : x(c.x), y(c.y), z(c.z) { }
	Coordinates::Coordinates(int x, int y) : x(x), y(y), z(0) { }
	Coordinates::Coordinates(int x, int y, int z) : x(x), y(y), z(z) { }

	Coordinates look(Direction::direction d) const
	{
		switch (d)
		{
			case Direction::top:
				return Coordinates(this->x, this->y + 1, this->z);
			case Direction::bottom:
				return Coordinates(this->x, this->y - 1, this->z);
			case Direction::left:
				return Coordinates(this->x - 1, this->y, this->z);
			case Direction::right:
				return Coordinates(this->x + 1, this->y, this->z);
			case Direction::front:
				return Coordinates(this->x, this->y, this->z + 1);
			case Direction::back:
				return Coordinates(this->x, this->y, this->z - 1);
			default:
				return Coordinates(this->x, this->y, this->z);
		}
	}

	Coordinates operator +(const Coordinates &b) const
	{
		return Coordinates (this->x + b.x, this->y + b.y, this->z + b.z);
	}

	bool operator <(const Coordinates &b) const
	{
		if (this->z == b.z)
		{
			if (this->y == b.y)
				return this->x < b.x;
			else
				return this->y < b.y;
		}
		else
			return this->z < b.z;
	}

	bool operator ==(const Coordinates &b) const
	{
		return (this->x == b.x) & (this->y == b.y) & (this->z == b.z);
	}
};

#endif
