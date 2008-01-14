#include "CellFactory.h"
#include "Organism.h"

using std::string;
using std::vector;

Organism::Organism(vector<Gene> d) : dna(d)
{
	this->cell_factory = new CellFactory(this);
	this->add_cell(this->cell_factory->create_cell(new Proteins()));
}

Organism::~Organism()
{
	delete this->cell_factory;
	for (vector<Cell *>::iterator i = this->cells.begin(); i != this->cells.end(); i++)
		delete *i;
}

void Organism::add_cell(Cell *c)
{
	this->cells.push_back(c);
}

void Organism::increment_tick()
{
	for (vector<Cell *>::iterator i = this->cells.begin(); i != this->cells.end(); i++)
		(*i)->increment_tick();
}

void Organism::remove_cell(vector<Cell *>::iterator cell)
{
	delete *cell;
	this->cells.erase(cell);
}

string Organism::to_string(unsigned int width, unsigned int height, unsigned int depth)
{
	return "";
}
