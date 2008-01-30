#ifndef COORDINATES
#define COORDINATES

#include "Direction.h"

struct Coordinates
{
	int x;							///< The x component of the cell's location
	int y;							///< The y component of the cell's location
	int z;							///< The z component of the cell's location

	Coordinates() : x(0), y(0), z(0) { }
	Coordinates(int x, int y, int z) : x(x), y(y), z(z) { }

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

	bool operator <(const Coordinates &b) const
	{
		return this->z <= b.z && this->y <= b.y && this->x < b.x;
/*
        for (int z=0;z<zLength;z++) {
            for (int y=0;y<yLength;y++) {
                for (int x=0;x<xLength;x++) {
					Celltype cType = ctArray[x][y][z];
					if (cType != null) {
						result += x + " " + y + " " + z + " " + cType.ordinal() + "\n";
					}
				} 
            }
        }
*/
	}

	bool operator ==(const Coordinates &b) const
	{
		return this->x == b.x && this->y == b.y && this->z == b.z;
	}
};

#endif
