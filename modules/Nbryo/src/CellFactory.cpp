#include "CellFactory.h"

CellFactory::CellFactory(Organism *o) : host(o)
{
	this->cell_count = 0;
}

Cell *CellFactory::create_cell(std::vector<Protein *> *proteins)
{
	if (this->cell_count == 0)
	{
		Coordinates c;
		c.x = 0;
		c.y = 0;
		c.z = 0;
		return create_cell(proteins, c);
	}
	else throw "Cannot create the zygote twice.";
}

Cell *CellFactory::create_cell(std::vector<Protein *> *proteins, Coordinates coords)
{
	Cell *c = new Cell(&this->host->dna, proteins, coords, this->cell_count++);
	this->host->add_cell(c);
	return c;
}
