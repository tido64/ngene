#include "CellFactory.h"
#include "Organism.h"

using std::make_pair;
using std::map;
using std::string;
using std::vector;

Organism::Organism(vector<Gene> d) : dna(d)
{
	this->cell_factory = new CellFactory(this);
	this->add_cell(this->cell_factory->create_zygote(new vector<Protein *>()));
}

Organism::~Organism()
{
	delete this->cell_factory;
	for (map<Coordinates, Cell *>::iterator i = this->cells.begin(); i != this->cells.end(); i++)
		delete i->second;
}

void Organism::add_cell(Cell *c)
{
	this->cells[c->get_location()] = c;
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

string Organism::to_string(unsigned int width, unsigned int height, unsigned int depth)
{
	return "";
}
