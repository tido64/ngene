#include "Cell.h"
//#include "Ribosome.h"

using std::string;
using std::vector;

Cell::Cell(const vector<Gene> *d, Proteins *p, Coordinates c, int id)
	: coordinates(c), dna(d), id(id), MAX_NUMBER_OF_PROTEINS(99)
{
	this->proteins = p;
	//this->proteins->make_aware(this);
}

Cell::~Cell()
{
	delete this->dna;
	delete this->proteins;
	delete this->ribosome;
}

void Cell::adjust_hormones() { }

void Cell::increment_tick()
{
	// gather parameters here
	// check and see if they are joint, and how they are used for the following calls
	this->translate("");
	this->adjust_hormones();
	this->divide();
	this->speciate();
}

void Cell::divide() { }

void Cell::speciate() { }

void Cell::translate(string promoter)
{
	if (this->proteins->count() <= this->MAX_NUMBER_OF_PROTEINS)
		for (vector<Gene>::const_iterator i = dna->begin(); i != dna->end(); i++)
			if (i->sequence.find(promoter) != string::npos)
				this->proteins->add(this->ribosome->translate(i));
}
