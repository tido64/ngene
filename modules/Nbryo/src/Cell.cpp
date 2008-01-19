#include "Cell.h"
#include "Ribosome.h"

using std::string;
using std::vector;

Cell::Cell(int id, const vector<Gene> *d, Coordinates c, vector<Protein *> *p)
	: MAX_NUMBER_OF_PROTEINS(99), id(id), dna(d), coordinates(c), proteins(p)
{
	for (vector<Protein*>::iterator i = this->proteins->begin(); i != this->proteins->end(); i++)
		(*i)->make_aware(this);
}

Cell::~Cell()
{
	for (vector<Protein*>::iterator i = this->proteins->begin(); i != this->proteins->end(); i++)
		delete *i;
	delete this->proteins;
	delete this->ribosome;
}

void Cell::adjust_hormones()
{
	vector<double> changes;
	changes.assign(Hormone::number_of_types, 0);

	/// Proteins can request adjustments to hormone concentrations. These
	/// changes are accumulated before being processed.
	///
	/// The maximum concentration is 1.0, so decisions have to be made whether
	/// more complex checks are needed.
	/// \param type The type of hormone to adjust
	/// \param amount The amount to adjust the hormone with
	//void adjust_hormones(const Hormone::Type type, const double &amount)
	//{
	//	this->hormone_changes[type] += amount;
	//}

//	for (vector<Protein *>::iterator i = this->active_proteins.begin(); i != this->active_proteins.end(); i++)


	for (unsigned int i = 0; i < changes.size(); i++)
		if (changes[i] != 0)
			this->hormones.adjust_concentration((Hormone::Type)i, changes[i]);
}

void Cell::divide() { }

void Cell::regulate_proteins()
{
	// Remove dead proteins
	for (vector<vector<Protein *>::iterator>::reverse_iterator i = this->dead_proteins.rbegin(); i != this->dead_proteins.rend(); i++)
	{
		delete **i;
		this->proteins->erase(*i);
	}
	this->dead_proteins.clear();
	this->active_proteins.clear();
	for (vector<Protein *>::iterator i = this->proteins->begin(); i != this->proteins->end(); i++)
	{
		// Age the proteins and add the dead/removable ones into a vector
		if ((*i)->age())
			this->dead_proteins.push_back(i);

		// If the protein is active, it will effect the cell in some way
		if ((*i)->is_active())
			this->active_proteins.push_back(*i);
	}
}

void Cell::speciate()
{
	//for (
}

void Cell::translate(string promoter)
{
	if (this->proteins->size() <= this->MAX_NUMBER_OF_PROTEINS)
		for (vector<Gene>::const_iterator i = dna->begin(); i != dna->end(); i++)
			if (i->sequence.find(promoter) != string::npos)
				this->proteins->push_back(this->ribosome->translate(i));
}

void Cell::increment_tick()
{
	// gather parameters here
	// check and see if they are joint, and how they are used for the following calls
	regulate_proteins();

	this->translate("");
	this->adjust_hormones();
	this->divide();
	this->speciate();
}
