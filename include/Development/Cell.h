/// A generic cell in a generic organism.

#ifndef CELL_H_
#define CELL_H_

#include <list>
#include "Message.h"
#include "Protein.h"

struct Cell
{
	int type;						///< The type of this cell
	std::list<Protein> proteins;	///< The proteins in this cell
	std::vector<double> chemicals;	///< The chemicals in this cell
	Coordinates coords;				///< The location of this cell
	std::vector<Message> messages;	///< Messages from the neighbouring cells in the current tick

	Cell() : type(-1)
	{
		this->messages.reserve(From::ALL_NEIGHBOURS);
	}

	Cell(const Cell &c, const Coordinates &loc) :
		type(c.type), proteins(c.proteins), chemicals(c.chemicals.size(), 0.0), coords(loc)
	{
		this->messages.reserve(From::ALL_NEIGHBOURS);
	}
};

#endif
