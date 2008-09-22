/// A generic cell in a generic organism.

#ifndef CELL
#define CELL

#include <list>
#include "Coordinates.h"
#include "Protein.h"

struct Message;

struct Cell
{
	int type;						///< The type of this cell
	std::list<Protein> proteins;	///< The proteins in this cell
	std::vector<double> chemicals;	///< The chemicals in this cell
	Coordinates coords;				///< The location of this cell
	std::vector<Message> messages;	///< Messages from the neighbouring cells in the current tick

	Cell() :
		messages(COORDINATES) { }

	Cell(const Cell &c, const Coordinates &l) :
		type(c.type),
		coords(l),
		messages(COORDINATES) { }
};

#include "Message.h"

#endif
