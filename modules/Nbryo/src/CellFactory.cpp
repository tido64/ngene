#include "CellFactory.h"
#include "Organism.h"

using std::vector;

CellFactory::CellFactory(Organism *o) : host(o), cell_count(0)
{
	// Transcribe all genes to make proteins for the zygote
	vector<Protein *> *proteins = new vector<Protein *>(this->host->dna.size());
	for (unsigned int i = 0; i < this->host->dna.size(); i++)
		proteins->push_back(new Protein(&this->host->dna[i]));

	// Create the zygote and make sure the proteins are aware of their host
	Cell *zygote = new Cell(this->cell_count++, this->host, Coordinates(0, 0, 0), proteins);
	this->host->add_cell(zygote);
	for (vector<Protein *>::iterator i = proteins->begin(); i != proteins->end(); i++)
		(*i)->make_aware(zygote);
}

void CellFactory::divide_cell(const Cell *mother, const Coordinates &location)
{
	this->host->add_cell(
		new Cell(this->cell_count++, this->host, location, new vector<Protein *>(*mother->get_proteins())));
}
