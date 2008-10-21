#include "ArtDev3D.h"

using std::list;
using std::map;
using std::stringstream;
using std::vector;

void ArtDev3D::cell_division(Cell &cell, const Coordinates &location)
{
	if (!exists(location) && !queued(location))
		divide_cell(cell, location);
}

void ArtDev3D::execute(Cell &c)
{
	ProteinListIterators
		active_proteins[ProteinType::number_of_types],
		dead_proteins;

	for (list<Protein>::iterator p = c.proteins.begin(); p != c.proteins.end(); p--)
	{
		// check chemical criteria
		bool chemically_active (true);
		for (unsigned int i = 0; i < c.chemicals.size(); i++)
			chemically_active &= c.chemicals[i] >= p->chemical_criteria[i];

		// ... now check neighbourhood criteria
		if (chemically_active
			& ((p->neighbourhood_criteria[0] == CellType::any) | (p->neighbourhood_criteria[0] == c.messages[From::above].type))
			& ((p->neighbourhood_criteria[1] == CellType::any) | (p->neighbourhood_criteria[1] == c.messages[From::below].type))
			& ((p->neighbourhood_criteria[2] == CellType::any) | (p->neighbourhood_criteria[2] == c.messages[From::left].type))
			& ((p->neighbourhood_criteria[3] == CellType::any) | (p->neighbourhood_criteria[3] == c.messages[From::right].type))
			& ((p->neighbourhood_criteria[4] == CellType::any) | (p->neighbourhood_criteria[4] == c.messages[From::front].type))
			& ((p->neighbourhood_criteria[5] == CellType::any) | (p->neighbourhood_criteria[5] == c.messages[From::back].type)))
		{
			active_proteins[p->type].push_back(p);
		}

		if (--p->life <= 0) // queue dead proteins
			dead_proteins.push_back(p);
	}

	if (!active_proteins[ProteinType::transcribing].empty() & (c.proteins.size() < this->max_protein_number))
		transcribe_proteins(c, active_proteins[ProteinType::transcribing]);
	if (!active_proteins[ProteinType::regulatory].empty())
		regulate_chemical_levels(c, active_proteins[ProteinType::regulatory]);
	if (!active_proteins[ProteinType::mitotic].empty())
		mitosis(c, active_proteins[ProteinType::mitotic]);
	if (!active_proteins[ProteinType::metamorphic].empty())
		metamorphosis(c, active_proteins[ProteinType::metamorphic]);

	// remove dead proteins
	for (ProteinListIterators::reverse_iterator i = dead_proteins.rbegin(); i != dead_proteins.rend(); i++)
		c.proteins.erase(*i);
}

void ArtDev3D::initialize(Organism *o)
{
	Cell c;
	this->genome.clear();
	for (Genotype::const_iterator i = o->genotype.begin(); i != o->genotype.end(); i++)
	{
		this->genome.push_back(boost::any_cast<Gene>(*i));
		c.proteins.push_back(*this->genome.back().get_protein());
	}
	c.chemicals.assign(this->genome.front().setup->chemicals_number, 0.0);
	c.type = static_cast<int>(CellType::a);
	o->cells[c.coords] = c;
}

void ArtDev3D::metamorphosis(Cell &cell, ProteinListIterators &proteins)
{
	if (this->cell_types < 2)
		return;

	double tmp (0.0);
	vector<double> tally (this->cell_types, 0.0);

	for (unsigned int p = 0; p < proteins.size(); p++)
		tally[proteins[p]->meta] += proteins[p]->parameters[0];

	for (unsigned int i = 0; i < tally.size(); i++)
	{
		if (tally[i] > this->min_stimuli_level && tally[i] > tmp)
		{
			cell.type = i;
			tmp = tally[i];
		}
	}
}

void ArtDev3D::mitosis(Cell &cell, ProteinListIterators &proteins)
{
	vector<double> stimuli (DIRECTIONS, 0.0);
	for (unsigned int p = 0; p < proteins.size(); p++)
		for (int i = 0; i < DIRECTIONS; i++)
			stimuli[i] += proteins[p]->parameters[i];

	if (stimuli[0] > this->min_stimuli_level)
		cell_division(cell, cell.coords.above());
	if (stimuli[1] > this->min_stimuli_level)
		cell_division(cell, cell.coords.below());
	if (stimuli[2] > this->min_stimuli_level)
		cell_division(cell, cell.coords.left());
	if (stimuli[3] > this->min_stimuli_level)
		cell_division(cell, cell.coords.right());
	if (stimuli[4] > this->min_stimuli_level)
		cell_division(cell, cell.coords.front());
	if (stimuli[5] > this->min_stimuli_level)
		cell_division(cell, cell.coords.back());
}

void ArtDev3D::regulate_chemical_levels(Cell &cell, ProteinListIterators &proteins)
{
	// Adjust all chemical levels accordingly
	for (unsigned int p = 0; p < proteins.size(); p++)
		for (unsigned int i = 0; i < proteins[p]->parameters.size(); i++)
			cell.chemicals[i] += proteins[p]->parameters[i];

	// Make sure the chemical levels are within reasonable values
	for (vector<double>::iterator i = cell.chemicals.begin(); i != cell.chemicals.end(); i++)
	{
		if (*i > this->max_chemical_concentration)
			*i = this->max_chemical_concentration;
		else if (*i < this->min_chemical_concentration)
			*i = this->min_chemical_concentration;
	}
}

void ArtDev3D::transcribe_proteins(Cell &cell, ProteinListIterators &proteins)
{
	for (unsigned int p = 0; p < proteins.size(); p++)
		for (Genome::iterator g = this->genome.begin(); g != this->genome.end(); g++)
			if (ngene::bitstring_find(proteins[p]->meta, g->setup->promoter_length, g->get_sequence(), g->setup->gene_sequence_length) > -1)
				cell.proteins.push_back(Protein (*g->get_protein()));
}
