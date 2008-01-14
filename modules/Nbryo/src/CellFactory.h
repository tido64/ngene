/// Code based off Johan Høye's [HOYE2006]. Rewritten in C++ for Ngene with
/// modifications, hopefully making things simpler and faster.

#ifndef CELLFACTORY
#define CELLFACTORY

#include "Cell.h"
#include "Organism.h"

class CellFactory
{
public:
	CellFactory(const Organism *o);
	Cell *create_cell(Proteins *proteins);
	Cell *create_cell(Proteins *proteins, Coordinates coords);

private:
	const Organism *host;		///< The organism that uses this factory
	unsigned int cell_count;	///< Keeps count of how many cells have been created
};

#endif
