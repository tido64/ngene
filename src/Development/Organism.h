/// A generic organism able to hold its dna and cells.

#ifndef ORGANISM
#define ORGANISM

#include <map>
#include "Cell.h"

class Organism
{
public:
	const Genotype genotype;				///< The organism's dna
	std::map<Coordinates, Cell> cells;		///< The organism's cells

	Organism(const Genotype &g) : genotype(g) { }
	//Organism(Organism o) : genotype(o.genotype), cells(o.cells) { }
};

#endif
