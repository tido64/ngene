#ifndef CELL
#define CELL

#include "Coordinates.h"
#include "Protein.h"

struct Cell
{
	int type;
	Coordinates coords;
	std::vector<double> chemicals;
	std::vector<Protein> proteins;
};

#endif
