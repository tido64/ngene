#include "CellFactory.h"
#include "Organism.h"

using std::make_pair;
using std::map;
using std::string;
using std::stringstream;
using std::vector;

Organism::Organism(const DNA &d, const Coordinates &b)
: dna(d), offset((b.x - 1) / 2, (b.y - 1) / 2, (b.z - 1) / 2)//, phenotype(0)
{
	this->cell_factory = new CellFactory(this);
	//this->phenotype = new map<Coordinates, CellType::Type>();
}

Organism::~Organism()
{
	delete this->cell_factory;
	for (map<Coordinates, Cell *>::iterator i = this->cells.begin(); i != this->cells.end(); i++)
		delete i->second;
}

void Organism::add_cell(Cell *c)
{
#ifdef CELL_OVERWRITE /*
* The following algorithm overwrites the location with a newly created
* cell. The problem with this algorithm is that it may overwrite the
* same cells every tick, preventing growth.
*/
	if (this->cells.find(c->get_location()) != this->cells.end())
	{
		this->working_cells[c->get_location()] = false;
		delete this->cells[c->get_location()];
	}
	this->cells[c->get_location()] = c;
	//(*this->phenotype)[c->get_location()] = c->get_type();

#else /*
* In this algorithm, if the location is already occupied by a cell, the
* newly created cell will be deleted.
*/
	if (this->cells.find(c->get_location()) != this->cells.end())
		delete c;
	else
	{
		this->cells[c->get_location()] = c;
		this->phenotype.insert(make_pair(c->get_location() + this->offset, c->get_type()));
	}
#endif
}

CellType::Type Organism::get_cell(const Coordinates &c)
{
	if (this->cells.find(c) != this->cells.end())
		return this->cells[c]->get_type();
	else
		return CellType::empty;
}

void Organism::increment_tick()
{
	// This algorithm prevents newly added/removed cells from ever being noticed of a tick
	this->working_cells.clear();
	for (map<Coordinates, Cell *>::iterator i = this->cells.begin(); i != this->cells.end(); i++)
		this->working_cells[i->first] = true;
	for (map<Coordinates, bool>::iterator i = this->working_cells.begin(); i != this->working_cells.end(); i++)
		if (i->second)
			this->cells[i->first]->increment_tick();
}

const map<Coordinates, CellType::Type> *Organism::get_phenotype()
{
	return new map<Coordinates, CellType::Type>(this->phenotype);
}

unsigned int Organism::size()
{
	return this->cells.size();
}
