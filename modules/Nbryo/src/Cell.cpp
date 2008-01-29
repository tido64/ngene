#include "Cell.h"
#include "CellFactory.h"
#include "Organism.h"
#include "Ribosome.h"

using std::string;
using std::vector;

Cell::Cell(int id, Organism *host, Coordinates c, vector<Protein *> *p)
	: MAX_NUMBER_OF_PROTEINS(99), STIMULUS_THRESHOLD(0.0), id(id), dna(host->dna), coordinates(c), organism(host), proteins(p)
{
	this->active_proteins.assign(ProteinType::number_of_types, vector<Protein *>());
	for (vector<vector<Protein *> >::iterator i = this->active_proteins.begin(); i != this->active_proteins.end(); i++)
		i->reserve(this->MAX_NUMBER_OF_PROTEINS);
	for (vector<Protein*>::iterator i = this->proteins->begin(); i != this->proteins->end(); i++)
		(*i)->make_aware(this);
	this->ribosome = new Ribosome(this);
}

Cell::~Cell()
{
	delete this->ribosome;
	for (vector<Protein*>::iterator i = this->proteins->begin(); i != this->proteins->end(); i++)
		delete *i;
	delete this->proteins;
}

void Cell::mitosis()
{
	// Accumulate stimuli in each directions
	vector<double> stimuli;
	stimuli.assign(this->coordinates.directions, 0.0);

	vector<Protein *> *proteins = &this->active_proteins[ProteinType::mitotic];
	for (vector<Protein *>::iterator p = proteins->begin(); p != proteins->end(); p++)
	{
		const vector<double> dir_stimulus = (*p)->parameters;
		for (unsigned int i = 0; i < this->coordinates.directions; i++)
			stimuli[i] += dir_stimulus[i];
	}

	// Look to divide in all directions with enough stimulus
	for (unsigned int i = 0; i < this->coordinates.directions; i++)
		if (stimuli[i] > this->STIMULUS_THRESHOLD)
			this->organism->cell_factory->divide_cell(this, this->coordinates.look((Direction::direction)i));
}

void Cell::regulate_hormones()
{
	// From active proteins, accumulate the changes that need to be made
	vector<double> changes;
	changes.assign(Hormone::number_of_types, 0);

	vector<Protein *> *proteins = &this->active_proteins[ProteinType::regulatory];
	for (vector<Protein *>::iterator p = proteins->begin(); p != proteins->end(); p++)
	{
		const vector<double> change = (*p)->parameters;
		for (int i = 0; i < Hormone::number_of_types; i++)
			changes[i] += change[i];
	}

	// Apply the changes
	for (unsigned int i = 0; i < changes.size(); i++)
		if (changes[i] != 0)
			this->hormones.adjust_concentration((Hormone::Type)i, changes[i]);
}

void Cell::regulate_proteins()
{
	// Remove dead proteins
	for (vector<vector<Protein *>::iterator>::reverse_iterator i = this->dead_proteins.rbegin(); i != this->dead_proteins.rend(); i++)
	{
		delete **i;
		this->proteins->erase(*i);
	}
	this->dead_proteins.clear();
	for (vector<vector<Protein *> >::iterator i = this->active_proteins.begin(); i != this->active_proteins.end(); i++)
		i->clear();
	for (vector<Protein *>::iterator i = this->proteins->begin(); i != this->proteins->end(); i++)
	{
		// Age the proteins and mark the dead/removable ones
		if ((*i)->age())
			this->dead_proteins.push_back(i);

		// If the protein is active, it will effect the cell in some way later in this tick
		if ((*i)->is_active())
			this->active_proteins[(*i)->type].push_back(*i);
	}
}

void Cell::speciate()
{
	// Accumulate stimuli from proteins
	vector<double> stimuli;
	stimuli.assign(CellType::number_of_types, 0.0);
	for (vector<Protein *>::iterator i = this->active_proteins[ProteinType::speciation].begin(); i != this->active_proteins[ProteinType::speciation].end(); i++)
	{
		const vector<double> stimulus = (*i)->parameters;
		stimuli[(int)stimulus[0]] += stimulus[1];
	}

	// Find highest stimulus
	int ct = -1;
	double highest = 0.0;
	for (int i = 0; i < CellType::number_of_types; i++)
	{
		if (stimuli[i] > highest)
		{
			ct = i;
			highest = stimuli[i];
		}
	}

	// Speciate only if the stimulus is above the threshold
	if (stimuli[ct] > 0 && stimuli[ct] > this->STIMULUS_THRESHOLD)
		this->type = (CellType::Type)ct;
}

void Cell::translate()
{
	// Given the number of proteins do not exceed the maximum allowed:
	//	For every active protein:
	//		For every gene:
	//			Check if gene sequence has protein promoter
	if (this->proteins->size() < this->MAX_NUMBER_OF_PROTEINS)
	{
		vector<Protein *> *proteins = &this->active_proteins[ProteinType::transcribing];
		for (vector<Protein *>::iterator p = proteins->begin(); p != proteins->end(); p++)
			for (unsigned int i = 0; i < this->dna.size(); i++)
				if ((*p)->find_promoter(this->dna[i].get_sequence()))
				{
					this->proteins->push_back(this->ribosome->translate(&this->dna[i]));
					if (this->proteins->size() >= this->MAX_NUMBER_OF_PROTEINS)
						return;
				}
	}
}

void Cell::get_neighbours(vector<CellType::Type> &neighbours) const
{
	neighbours.reserve(Direction::number_of_directions);
	for (int i = 0; i < Direction::number_of_directions; i++)
		neighbours.push_back(this->organism->get_cell(this->coordinates.look((Direction::direction)i)));
}

void Cell::increment_tick()
{
	regulate_proteins();
	translate();
	regulate_hormones();
	mitosis();
	speciate();
}
