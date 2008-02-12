/// Code based off Johan Høye's [HOYE2006]. Rewritten in C++ for Ngene with
/// modifications, hopefully making things simpler and faster.

#ifndef CELLFACTORY
#define CELLFACTORY

#include "Cell.h"

class CellFactory
{
public:
	/// Initializes CellFactory and creates the initial cell, the zygote, and
	/// the initial set of proteins.
	/// \param o The organism to build cells for
	CellFactory(Organism *o);

	virtual ~CellFactory() { };

	void create_zygote();

	/// Divides a mother cell into two daughter cells, a process called
	/// cytokinesis, in given direction.
	/// \param mother	The mother cell to divide
	/// \param location	The location to put the new cell
	virtual void divide_cell(const Cell *mother, const Coordinates &location);

private:
	Organism *host;	///< The organism that uses this factory
};

#endif
