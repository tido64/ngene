#include "Coordinates.h"

Coordinates::Coordinates() : x(0), y(0), z(0) { }
Coordinates::Coordinates(int x, int y, int z) : x(x), y(y), z(z) { }

Coordinates Coordinates::look(Direction::direction d) const
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

bool Coordinates::operator <(const Coordinates &b) const
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

bool Coordinates::operator ==(const Coordinates &b) const
{
	return (this->x == b.x) && (this->y == b.y) && (this->z == b.z);
}
