#include "../../../src/Development/AbstractDevelopment.h"
#include "../../../src/Development/Organism.h"
#include "Gene.h"
#include "ProteinType.h"

typedef std::vector< std::list<Protein>::iterator > ProteinListIterators;

class ArtDev3D : public AbstractDevelopment
{
private:
	const unsigned int max_protein_number;
	unsigned int cell_types;
	const double
		max_chemical_concentration,
		min_chemical_concentration,
		min_stimuli_level;
	std::map<Coordinates, Cell> new_cells;

	void cell_division(Cell *cell, ProteinListIterators &activated_proteins);
	void divide_cell(Cell *cell, Coordinates location);
	void metamorphosis(Cell *cell, ProteinListIterators &activated_proteins);
	void regulate_chemical_levels(Cell *cell, ProteinListIterators &activated_proteins);
	void transcribe_proteins(Cell *cell, ProteinListIterators &activated_proteins);

public:
	ArtDev3D() : AbstractDevelopment(10), max_protein_number(99), max_chemical_concentration(1.0), min_chemical_concentration(0.0), min_stimuli_level(0.0) { }
	ArtDev3D(int t) : AbstractDevelopment(t), max_protein_number(99), max_chemical_concentration(1.0), min_chemical_concentration(0.0), min_stimuli_level(0.0) { }
	void execute();
	const char *to_string();
};
