#ifndef ORGANISM
#define ORGANISM

#include <map>
#include "Cell.h"

class Organism
{
public:
	Cell *active_cell;						///< The cell undergoing changes
	std::map<Coordinates, Cell> cells;		///< The organism's cells
	std::map<Coordinates, Cell> new_cells;	///< The organism's new cells
	const Genotype genotype;				///< The organism's dna

	Organism(Genotype g) : genotype(g) {}
};

#endif
