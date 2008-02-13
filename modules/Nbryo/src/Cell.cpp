#include "Cell.h"
#include "CellFactory.h"
#include "Organism.h"
#include "Ribosome.h"

using std::string;
using std::vector;

Cell::Cell(Organism *host, const std::vector<Protein> &p)
: MAX_NUMBER_OF_PROTEINS(99), STIMULUS_THRESHOLD(0.0), id(0), type(CellType::a), dna(host->dna), coordinates(0,0,0), organism(host), proteins(p)
{
	engage_cytokinesis();
}

Cell::Cell(int id, const Cell *mother, const Coordinates &c)
: MAX_NUMBER_OF_PROTEINS(mother->MAX_NUMBER_OF_PROTEINS), STIMULUS_THRESHOLD(mother->STIMULUS_THRESHOLD), id(id), type(mother->type), dna(mother->dna), coordinates(c), organism(mother->organism), proteins(mother->proteins)
{
	engage_cytokinesis();
}

Cell::~Cell()
{
	delete this->ribosome;
}

void Cell::engage_cytokinesis()
{
	this->active_proteins.reserve(ProteinType::number_of_types);
	for (int i = 0; i < ProteinType::number_of_types; i++)
	{
		this->active_proteins.push_back(vector<unsigned int>());
		this->active_proteins.rbegin()->reserve(this->MAX_NUMBER_OF_PROTEINS);
	}
	this->ribosome = new Ribosome(this);
}

double Cell::get_hormones(const Hormone::Type type) const
{
	return this->hormones.get_concentration(type);
}

Coordinates Cell::get_location() const
{
	return this->coordinates;
}

void Cell::get_neighbourhood(vector<CellType::Type> &neighbourhood) const
{
	neighbourhood.reserve(Direction::number_of_directions);
	for (int i = 0; i < Direction::number_of_directions; i++)
		neighbourhood.push_back(this->organism->get_cell(this->coordinates.look((Direction::direction)i)));
}

CellType::Type Cell::get_type() const
{
	return this->type;
}

void Cell::increment_tick()
{
	regulate_proteins();
	translate();
	regulate_hormones();
	mitosis();
	speciate();
}

void Cell::mitosis()
{
	if (!this->active_proteins[ProteinType::mitotic].empty())
	{
		// Accumulate stimuli in each directions
		vector<unsigned int>::iterator p = this->active_proteins[ProteinType::mitotic].begin();
		vector<double> stimuli (*this->proteins[*p].get_parameters());

		for (p++; p != this->active_proteins[ProteinType::mitotic].end(); p++)
		{
			const std::vector<double> *parameters = this->proteins[*p].get_parameters();
			for (unsigned int i = 0; i < Direction::number_of_directions; i++)
				stimuli[i] += parameters->at(i);
		}

		// Look to divide in all directions with enough stimulus
		for (unsigned int i = 0; i < Direction::number_of_directions; i++)
			if (stimuli[i] > this->STIMULUS_THRESHOLD)
				this->organism->cell_factory->divide_cell(this, this->coordinates.look((Direction::direction)i));
	}
}

void Cell::regulate_hormones()
{
	if (!this->active_proteins[ProteinType::regulatory].empty())
	{
		// From active proteins, accumulate the changes that need to be made
		vector<unsigned int>::iterator p = this->active_proteins[ProteinType::regulatory].begin();
		vector<double> changes (*this->proteins[*p].get_parameters());

		for (p++; p != this->active_proteins[ProteinType::regulatory].end(); p++)
		{
			const std::vector<double> *parameters = this->proteins[*p].get_parameters();
			for (unsigned int i = 0; i < parameters->size(); i++)
				changes[i] += parameters->at(i);
		}

		// Apply the changes
		for (unsigned int i = 0; i < changes.size(); i++)
			if (changes[i] != 0)
				this->hormones.adjust_concentration((Hormone::Type)i, changes[i]);
	}
}

void Cell::regulate_proteins()
{
	for (vector<vector<unsigned int> >::iterator i = this->active_proteins.begin(); i != this->active_proteins.end(); i++)
		i->clear();

	// Remove dead proteins
	for (vector<unsigned int>::reverse_iterator i = this->dead_proteins.rbegin(); i != this->dead_proteins.rend(); i++)
		this->proteins.erase(this->proteins.begin() + *i);
	this->dead_proteins.clear();

	for (unsigned int i = 0; i != this->proteins.size(); i++)
	{
		// Age the proteins and mark the dead/removable ones
		if (this->proteins[i].age())
			this->dead_proteins.push_back(i);

		// If the protein is acive, it will effect the cell in some way later in this tick
		if (this->proteins[i].is_active())
			this->active_proteins[this->proteins[i].get_type()].push_back(i);
	}
}

void Cell::speciate()
{
	if (!this->active_proteins[ProteinType::speciation].empty())
	{
		// Accumulate stimuli from proteins
		vector<double> stimuli;
		stimuli.assign(CellType::number_of_types, 0.0);
		for (vector<unsigned int>::iterator i = this->active_proteins[ProteinType::speciation].begin(); i != this->active_proteins[ProteinType::speciation].end(); i++)
		{
			const vector<double> *parameters = this->proteins[*i].get_parameters();
			stimuli[(int)parameters->at(0)] += parameters->at(1);
		}

		// Find highest stimulus
		int ct = this->type;
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
}

void Cell::translate()
{
	// Given the number of proteins do not exceed the maximum allowed:
	//	For every active protein:
	//		For every gene:
	//			Check if gene sequence has protein promoter
	if (!this->active_proteins[ProteinType::transcribing].empty() && this->proteins.size() < this->MAX_NUMBER_OF_PROTEINS)
	{
		for (vector<unsigned int>::iterator p = this->active_proteins[ProteinType::transcribing].begin(); p != this->active_proteins[ProteinType::transcribing].end(); p++)
			for (unsigned int i = 0; i < this->dna.size(); i++)
				if (this->proteins[*p].find_promoter(this->dna[i].get_sequence()))
				{
					this->ribosome->translate(&this->dna[i]);
					if (this->proteins.size() >= this->MAX_NUMBER_OF_PROTEINS)
						return;
				}
	}
}
