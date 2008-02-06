#ifndef COORDINATES
#define COORDINATES

#include "Direction.h"

class Coordinates
{
public:
	int x;	///< The x component of the cell's location
	int y;	///< The y component of the cell's location
	int z;	///< The z component of the cell's location

	Coordinates();
	Coordinates(int x, int y, int z);

	Coordinates look(Direction::direction d) const;

	bool operator <(const Coordinates &b) const;

	bool operator ==(const Coordinates &b) const;
};

#endif
