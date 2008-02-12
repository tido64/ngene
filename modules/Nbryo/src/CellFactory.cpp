#include "CellFactory.h"
#include "Organism.h"

using std::vector;

CellFactory::CellFactory(Organism *o) : host(o)
{
	// Transcribe all genes to make proteins for the zygote
	vector<Protein> proteins;
	proteins.reserve(this->host->dna.size() * 2);
	for (unsigned int i = 0; i < this->host->dna.size(); i++)
		proteins.push_back(Protein(&this->host->dna[i]));

	// Create the zygote
	this->host->add_cell(new Cell(this->host, proteins));
}

void CellFactory::divide_cell(const Cell *mother, const Coordinates &location)
{
	if (location.x <= this->host->offset.x
	&& location.y <= this->host->offset.y
	&& location.z <= this->host->offset.z
	&& location.x + this->host->offset.x >= 0
	&& location.y + this->host->offset.y >= 0
	&& location.z + this->host->offset.z >= 0)
		this->host->add_cell(new Cell(this->host->size(), mother, location));
}
