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
	{
#ifdef CELL_OVERWRITE /*
* The following algorithm overwrites the location with a newly created cell.
* The problem with this algorithm is that it may overwrite the same cells every
* tick, preventing growth.
*/
		this->host->remove_cell(location);
		this->host->add_cell(new Cell(this->host->size(), mother, location));

#else /*
* In this algorithm, if the location is already occupied by a cell, no cell
* will be added.
*/
		if (this->host->get_cell(location) == CellType::empty)
			this->host->add_cell(new Cell(this->host->size(), mother, location));
#endif
	}
}
