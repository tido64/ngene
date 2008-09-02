#ifndef CELL
#define CELL

#include <list>
#include "Coordinates.h"
#include "Protein.h"

struct Cell
{
	int type;
	std::list<Protein> proteins;
	std::vector<double> chemicals;
	Coordinates coords;
};

#endif
