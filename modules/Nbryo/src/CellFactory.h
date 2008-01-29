/// Code based off Johan Høye's [HOYE2006]. Rewritten in C++ for Ngene with
/// modifications, hopefully making things simpler and faster.

#ifndef CELLFACTORY
#define CELLFACTORY

#include "Cell.h"

class CellFactory
{
public:
	CellFactory(Organism *o);
	virtual ~CellFactory() { };

	/// Creates the initial cell, the zygote.
	Cell *create_zygote(std::vector<Protein *> *proteins);

	/// Divides a mother cell into two daughter cells, a process called
	/// cytokinesis, in given direction.
	/// \param mother	The mother cell to divide
	/// \param location	The location to put the new cell
	virtual void divide_cell(Cell const *mother, const Coordinates &location);

private:
	Organism *host;				///< The organism that uses this factory
	unsigned int cell_count;	///< Keeps count of how many cells have been created
};

#endif
