#ifndef COORDINATES_H_
#define COORDINATES_H_

namespace From
{
	enum Type
	{
		above,
		above_left,
		above_right,
		left,
		right,
		below,
		below_left,
		below_right,
		front,
		back,
		ALL_NEIGHBOURS
	};
}

struct Coordinates
{
	int x,	///< The x component of a cell's location
		y,	///< The y component of a cell's location
		z;	///< The z component of a cell's location

	Coordinates(int x = 0, int y = 0, int z = 0) : x(x), y(y), z(z) { }
	Coordinates(const Coordinates &c) : x(c.x), y(c.y), z(c.z) { }

	Coordinates above() const
	{
		return Coordinates(this->x, this->y + 1, this->z);
	}

	Coordinates above_left() const
	{
		return Coordinates(this->x - 1, this->y + 1, this->z);
	}

	Coordinates above_right() const
	{
		return Coordinates(this->x + 1, this->y + 1, this->z);
	}

	Coordinates below() const
	{
		return Coordinates(this->x, this->y - 1, this->z);
	}

	Coordinates below_left() const
	{
		return Coordinates(this->x - 1, this->y - 1, this->z);
	}

	Coordinates below_right() const
	{
		return Coordinates(this->x + 1, this->y - 1, this->z);
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

	const Coordinates operator +(const Coordinates &b) const
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
