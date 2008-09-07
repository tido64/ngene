#include "ArtDev3D.h"

using std::list;
using std::map;
using std::stringstream;
using std::vector;

void ArtDev3D::execute()
{
	for (map<Coordinates, Cell>::iterator c = this->organism->cells.begin(); c != this->organism->cells.end(); c++)
	{
		Cell *cell = &c->second;
		ProteinListIterators
			active_proteins[ProteinType::number_of_types],
			dead_proteins;

		for (list<Protein>::iterator p = cell->proteins.begin(); p != cell->proteins.end(); p--)
		{
			// check chemical criteria
			bool chemically_active (true);
			for (unsigned int i = 0; i < cell->chemicals.size(); i++)
			{
				if (cell->chemicals[i] < p->chemical_criteria[i])
				{
					chemically_active = false;
					break;
				}
			}

			// ... now check neighbourhood criteria
			if (chemically_active && ((this->organism->cells[cell->coords.above()].type == p->neighbourhood_criteria[0])
					& (this->organism->cells[cell->coords.below()].type == p->neighbourhood_criteria[1])
					& (this->organism->cells[cell->coords.left()].type == p->neighbourhood_criteria[2])
					& (this->organism->cells[cell->coords.right()].type == p->neighbourhood_criteria[3])
					& (this->organism->cells[cell->coords.front()].type == p->neighbourhood_criteria[4])
					& (this->organism->cells[cell->coords.back()].type == p->neighbourhood_criteria[5])))
				active_proteins[p->type].push_back(p);

			if (--p->life <= 0) // queue dead proteins
				dead_proteins.push_back(p);
		}

		if (!active_proteins[ProteinType::transcribing].empty() & (cell->proteins.size() < this->max_protein_number))
			transcribe_proteins(cell, active_proteins[ProteinType::transcribing]);
		if (!active_proteins[ProteinType::regulatory].empty())
			regulate_chemical_levels(cell, active_proteins[ProteinType::regulatory]);
		if (!active_proteins[ProteinType::mitotic].empty())
			mitosis(cell, active_proteins[ProteinType::mitotic]);
		if (!active_proteins[ProteinType::speciation].empty())
			metamorphosis(cell, active_proteins[ProteinType::speciation]);

		// remove dead proteins
		for (ProteinListIterators::reverse_iterator i = dead_proteins.rbegin(); i != dead_proteins.rend(); i++)
			c->second.proteins.erase(*i);
	}

	// move the new cells to the organism
	this->organism->cells.insert(this->new_cells.begin(), this->new_cells.end());
	this->new_cells.clear();
}

void ArtDev3D::mitosis(Cell *cell, ProteinListIterators &proteins)
{
	vector<double> stimuli (DIRECTIONS, 0.0);
	for (unsigned int p = 0; p < proteins.size(); p++)
		for (int i = 0; i < DIRECTIONS; i++)
			stimuli[i] += proteins[p]->parameters[i];

	if (stimuli[0] > this->min_stimuli_level)
		divide_cell(cell, cell->coords.above());
	if (stimuli[1] > this->min_stimuli_level)
		divide_cell(cell, cell->coords.below());
	if (stimuli[2] > this->min_stimuli_level)
		divide_cell(cell, cell->coords.left());
	if (stimuli[3] > this->min_stimuli_level)
		divide_cell(cell, cell->coords.right());
	if (stimuli[4] > this->min_stimuli_level)
		divide_cell(cell, cell->coords.front());
	if (stimuli[5] > this->min_stimuli_level)
		divide_cell(cell, cell->coords.back());
}

void ArtDev3D::divide_cell(Cell *cell, Coordinates location)
{
	if (this->organism->cells.find(location) != this->organism->cells.end()
		&& this->new_cells.find(location) != this->new_cells.end())
	{
		Cell new_cell;
		new_cell.coords = location;
		new_cell.type = cell->type;
		this->new_cells[location] = new_cell;
	}
}

void ArtDev3D::metamorphosis(Cell *cell, ProteinListIterators &proteins)
{
	double tmp (0.0);
	vector<double> tally (this->cell_types, 0.0);

	for (unsigned int p = 0; p < proteins.size(); p++)
		tally[proteins[p]->meta] += proteins[p]->parameters[0];

	for (unsigned int i = 0; i < tally.size(); i++)
	{
		if (tally[i] > this->min_stimuli_level && tally[i] > tmp)
		{
			cell->type = i;
			tmp = tally[i];
		}
	}
}

void ArtDev3D::regulate_chemical_levels(Cell *cell, ProteinListIterators &proteins)
{
	// Adjust all chemical levels accordingly
	for (unsigned int p = 0; p < proteins.size(); p++)
		for (unsigned int i = 0; i < proteins[p]->parameters.size(); i++)
			cell->chemicals[i] += proteins[p]->parameters[i];

	// Make sure the chemical levels are within reasonable values
	for (vector<double>::iterator i = cell->chemicals.begin(); i != cell->chemicals.end(); i++)
	{
		if (*i > this->max_chemical_concentration)
			*i = this->max_chemical_concentration;
		else if (*i < this->min_chemical_concentration)
			*i = this->min_chemical_concentration;
	}
}

void ArtDev3D::transcribe_proteins(Cell *cell, ProteinListIterators &proteins)
{
	for (unsigned int p = 0; p < proteins.size(); p++)
	{
		for (Genotype::const_iterator g = this->organism->genotype.begin(); g != this->organism->genotype.end(); g++)
		{
			Gene gene = boost::any_cast<Gene>(g);
			if (Ngene::bitstring_find(proteins[p]->meta, gene.setup->promoter_length, gene.get_sequence(), gene.setup->gene_sequence_length) > -1)
				cell->proteins.push_back(Protein (*gene.get_protein()));
		}
	}
}
