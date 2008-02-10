/// Code based off Johan Høye's [HOYE2006]. Rewritten in C++ for Ngene with
/// modifications, hopefully making things simpler and faster.
///
/// Modifications to this class includes the removal of the boundaries
/// concept. Organisms should be stable in the sense of how much they can grow,
/// thus there should be no need to know an organism's boundaries.

#ifndef ORGANISM
#define ORGANISM

//#define CELL_OVERWRITE						///< Enables cell overwriting algorithm

#include <map>
#include <sstream>
#include "Cell.h"

class CellFactory;

class Organism
{
public:
	const DNA dna;							///< The organism's dna
	CellFactory *cell_factory;				///< Responsible for creating all cells

	Organism(const DNA &d);
	virtual ~Organism();

	/// Adds a cell to the organism.
	virtual void add_cell(Cell *c);

	/// Returns the type of cell occupied in given coordinates.
	CellType::Type get_cell(const Coordinates &c);

	/// Fires a tick event. Currently, the cells are notified in the order
	/// of their creation instead of "simultaneously".
	virtual void increment_tick();

	const std::map<Coordinates, CellType::Type> *phenotype();

	unsigned int size();

private:
	std::map<Coordinates, Cell *> cells;		///< The cells this organism consists of
	std::map<Coordinates, bool> working_cells;	///< The cells that are working in current tick
	std::string output;
};

#endif
