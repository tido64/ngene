#include "CellFactory.h"
#include "Organism.h"

using std::vector;

CellFactory::CellFactory(Organism *o) : host(o)
{
	this->cell_count = 0;
}

Cell *CellFactory::create_zygote(std::vector<Protein *> *proteins)
{
	if (this->cell_count == 0)
	{
		Cell *c = new Cell(this->cell_count++, this->host, Coordinates(0, 0, 0), proteins);
		this->host->add_cell(c);
		return c;
	}
	else throw "Cannot create the zygote twice.";
}

void CellFactory::divide_cell(Cell *mother, Coordinates &location)
{
	this->host->add_cell(
		new Cell(this->cell_count++, this->host, location, new vector<Protein *>(*mother->get_proteins())));
}
