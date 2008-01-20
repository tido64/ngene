#include "Cell.h"
#include "Ribosome.h"

using std::string;
using std::vector;

Cell::Cell(int id, const vector<Gene> *d, Coordinates c, vector<Protein *> *p)
	: MAX_NUMBER_OF_PROTEINS(99), id(id), dna(d), coordinates(c), proteins(p)
{
	this->active_proteins.assign(ProteinType::number_of_types, vector<Protein *>());
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

void Cell::divide() { }

void Cell::regulate_hormones()
{
	// From active proteins, accumulate the changes that need to be made
	vector<Protein *> *proteins = &this->active_proteins[ProteinType::adjusting];
	vector<double> changes;
	changes.assign(Hormone::number_of_types, 0);
	for (vector<Protein *>::iterator p = proteins->begin(); p != proteins->end(); p++)
	{
		const vector<double> *change = (*p)->read();
		for (int i = 0; i < Hormone::number_of_types; i++)
			changes[i] += change->at(i);
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
	//for (
}

void Cell::translate()
{
	//if (this->proteins->size() <= this->MAX_NUMBER_OF_PROTEINS)
	//	for (vector<Gene>::const_iterator i = dna->begin(); i != dna->end(); i++)
	//		if (i->sequence.find(promoter) != string::npos)
	//			this->proteins->push_back(this->ribosome->translate(i));
}

void Cell::increment_tick()
{
	regulate_proteins();
	translate();
	regulate_hormones();
	divide();
	speciate();
}
