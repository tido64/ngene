#include "CellFactory.h"
#include "Organism.h"

using std::make_pair;
using std::map;
using std::string;
using std::vector;

Organism::Organism(const DNA &d) : dna(d)
{
	this->cell_factory = new CellFactory(this);
}

Organism::~Organism()
{
	delete this->cell_factory;
	for (map<Coordinates, Cell *>::iterator i = this->cells.begin(); i != this->cells.end(); i++)
		delete i->second;
}

void Organism::add_cell(Cell *c)
{
	if (this->cells.find(c->get_location()) != this->cells.end())
		delete this->cells[c->get_location()];
	this->cells[c->get_location()] = c;
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
	for (map<Coordinates, Cell *>::iterator i = this->cells.begin(); i!= this->cells.end(); i++)
		i->second->increment_tick();
}

void Organism::remove_cell(Cell *cell)
{
	this->cells.erase(cell->get_location());
	delete cell;
}

string Organism::to_string() const
{
	string s;
	for (map<Coordinates, Cell *>::const_iterator i = this->cells.begin(); i != this->cells.end(); i++)
	{
		s += i->first.x;
		s += " ";
		s += i->first.y;
		s += " ";
		s += i->first.z;
		s += " ";
		s += NUtility::to_string<int>(i->second->get_type());
		s += "\n";
	}
	return s;
}
