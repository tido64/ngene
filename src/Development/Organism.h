/// A generic organism to be used in development systems.

#ifndef ORGANISM_H_
#define ORGANISM_H_

#include <map>
#include "../Specimen.h"
#include "Cell.h"

class Organism
{
public:
	const Genotype genotype;			///< The organism's dna
	std::map<Coordinates, Cell> cells;	///< The organism's cells

	Organism(const Genotype &g) : genotype(g) { }
};

#endif
