#include "CellFactory.h"
#include "Organism.h"

using std::vector;

CellFactory::CellFactory(Organism *o) : host(o)
{
	// Transcribe all genes to make proteins for the zygote
	vector<Protein> *proteins = new vector<Protein>();
	proteins->reserve(this->host->dna.size());
	for (unsigned int i = 0; i < this->host->dna.size(); i++)
		proteins->push_back(Protein(&this->host->dna[i]));

	// Create the zygote
	Cell *zygote = new Cell(this->host->size(), this->host, Coordinates(0, 0, 0), proteins);
	this->host->add_cell(zygote);
}

void CellFactory::divide_cell(const Cell *mother, const Coordinates &location)
{
	Cell *daughter = new Cell(this->host->size(), this->host, location, mother->get_proteins());
	this->host->add_cell(daughter);
}
