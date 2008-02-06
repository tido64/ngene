#include "Cell.h"
#include "CellFactory.h"
#include "Organism.h"
#include "Ribosome.h"

using std::string;
using std::vector;

Cell::Cell(int id, Organism *host, Coordinates c, const vector<Protein> *p)
	: MAX_NUMBER_OF_PROTEINS(99), STIMULUS_THRESHOLD(0.0), id(id), dna(host->dna), coordinates(c), organism(host), proteins(*p)
{
	this->active_proteins.reserve(ProteinType::number_of_types);
	for (int i = 0; i < ProteinType::number_of_types; i++)
	{
		this->active_proteins.push_back(vector<Protein *>());
		this->active_proteins.rbegin()->reserve(this->MAX_NUMBER_OF_PROTEINS);
	}
	for (vector<Protein>::iterator i = this->proteins.begin(); i != this->proteins.end(); i++)
		i->make_aware(this);
	this->ribosome = new Ribosome(this);
}

Cell::~Cell()
{
	delete this->ribosome;
}

void Cell::mitosis()
{
	// Accumulate stimuli in each directions
	vector<double> stimuli;
	stimuli.assign(Direction::number_of_directions, 0.0);

	vector<Protein *> *proteins = &this->active_proteins[ProteinType::mitotic];
	for (vector<Protein *>::iterator p = proteins->begin(); p != proteins->end(); p++)
	{
		const std::vector<double> *parameters = (*p)->get_parameters();
		for (unsigned int i = 0; i < Direction::number_of_directions; i++)
			stimuli[i] += parameters->at(i);
	}

	// Look to divide in all directions with enough stimulus
	for (unsigned int i = 0; i < Direction::number_of_directions; i++)
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
		const std::vector<double> *parameters = (*p)->get_parameters();
		for (unsigned int i = 0; i < parameters->size(); i++)
			changes[i] += parameters->at(i);
	}

	// Apply the changes
	for (unsigned int i = 0; i < changes.size(); i++)
		if (changes[i] != 0)
			this->hormones.adjust_concentration((Hormone::Type)i, changes[i]);
}

void Cell::regulate_proteins()
{
	// Remove dead proteins
	for (vector<vector<Protein>::iterator>::reverse_iterator i = this->dead_proteins.rbegin(); i != this->dead_proteins.rend(); i++)
		this->proteins.erase(*i);
	this->dead_proteins.clear();

	for (vector<vector<Protein *> >::iterator i = this->active_proteins.begin(); i != this->active_proteins.end(); i++)
		i->clear();
	for (vector<Protein>::iterator i = this->proteins.begin(); i != this->proteins.end(); i++)
	{
		// Age the proteins and mark the dead/removable ones
		if (i->age())
			this->dead_proteins.push_back(i);

		// If the protein is active, it will effect the cell in some way later in this tick
		if (i->is_active())
			this->active_proteins[i->get_type()].push_back(&*i);
	}
}

void Cell::speciate()
{
	// Accumulate stimuli from proteins
	vector<double> stimuli;
	stimuli.assign(CellType::number_of_types, 0.0);
	for (vector<Protein *>::iterator i = this->active_proteins[ProteinType::speciation].begin(); i != this->active_proteins[ProteinType::speciation].end(); i++)
	{
		const vector<double> *parameters = (*i)->get_parameters();
		stimuli[(int)parameters->at(0)] += parameters->at(1);
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
	if (this->proteins.size() < this->MAX_NUMBER_OF_PROTEINS)
	{
		vector<Protein *> *proteins = &this->active_proteins[ProteinType::transcribing];
		for (vector<Protein *>::iterator p = proteins->begin(); p != proteins->end(); p++)
			for (unsigned int i = 0; i < this->dna.size(); i++)
				if ((*p)->find_promoter(this->dna[i].get_sequence()))
				{
					this->ribosome->translate(&this->dna[i]);
					if (this->proteins.size() >= this->MAX_NUMBER_OF_PROTEINS)
						return;
				}
	}
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

const vector<Protein> *Cell::get_proteins() const
{
	return &this->proteins;
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
