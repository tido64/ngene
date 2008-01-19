/// Code based off Johan Hoeye's [HOYE2006]. Rewritten in C++ for Ngene with
/// modifications, hopefully making things simpler and faster.
///
/// Modifications to this class includes the removal of the boundaries
/// concept. Organisms should be stable in the sense of how much they can grow,
/// thus there should be no need to know an organism's boundaries.

#ifndef ORGANISM
#define ORGANISM

#include <map>

#include "Coordinates.h"
#include "Gene.h"

class Cell;
class CellFactory;

class Organism
{
public:
	const std::vector<Gene> dna;			///< The organism's dna
	CellFactory *cell_factory;				///< Responsible for creating all cells

	Organism(std::vector<Gene> d);
	virtual ~Organism();

	/// Adds a cell to the organism.
	virtual void add_cell(Cell *c);

	/// Fires a tick event. Currently, the cells are notified in an order
	/// instead of "simultaneously".
	virtual void increment_tick();

	/// Removes and erases a cell from the organism.
	void remove_cell(Cell *cell);

	std::string to_string(unsigned int width, unsigned int height, unsigned int depth);

private:
	std::map<Coordinates, Cell *> cells;	///< The cells this organism consists of
};

#endif
