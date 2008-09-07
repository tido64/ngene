/// A generic cell in a generic organism.

#ifndef CELL
#define CELL

#include <list>
#include "Coordinates.h"
#include "Protein.h"

struct Cell
{
	int type;						///< The type of this cell
	std::list<Protein> proteins;	///< The proteins in this cell
	std::vector<double> chemicals;	///< The chemicals in this cell
	Coordinates coords;				///< The location of this cell
};

#endif
