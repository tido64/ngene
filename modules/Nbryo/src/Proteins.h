/// Code based off Johan Høye's [HOYE2006]. Rewritten in C++ for Ngene with
/// modifications, hopefully making things simpler and faster.

#ifndef PROTEINS
#define PROTEINS

#include "ProteinMolecule.h"

class Cell;

class Proteins
{
public:
	Proteins();
	~Proteins();

	/// Adds a single protein molecule to the cell
	void add(ProteinMolecule *p);

	/// Returns the number of proteins in the cell
	int count() { return this->proteins.size(); }

	/// Notifies every protein of a tick
	void increment_tick();

private:
	std::vector<ProteinMolecule *> proteins;								///< Pointers to all proteins in the cell
	std::vector<std::vector<ProteinMolecule *>::iterator> dead_proteins;	///< Dead proteins to be removed in the next tick
};

#endif
