#include "Cell.h"
#include "Proteins.h"

using std::vector;

Proteins::Proteins()
{
	this->dead_proteins.reserve(128);
}

Proteins::~Proteins()
{
	for (vector<ProteinMolecule *>::iterator i = this->proteins.begin(); i != this->proteins.end(); i++)
		delete *i;
}

void Proteins::add(ProteinMolecule *p)
{
	this->proteins.push_back(p);
}

void Proteins::increment_tick()
{
	// Remove dead proteins
	for (vector<vector<ProteinMolecule *>::iterator>::reverse_iterator i = this->dead_proteins.rbegin(); i != this->dead_proteins.rend(); i++)
	{
		delete **i;
		this->proteins.erase(*i);
	}
	this->dead_proteins.clear();

	for (vector<ProteinMolecule *>::iterator i = this->proteins.begin(); i != this->proteins.end(); i++)
	{
		// Age the proteins and add the dead/removable ones into a vector
		if ((*i)->age())
			this->dead_proteins.push_back(i);

		// Tell all active proteins to perform their actions
		if ((*i)->is_active())
			(*i)->perform_action();
	}
}
