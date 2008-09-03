#if defined( WIN32) && defined(_DEBUG)
#pragma warning(disable: 4267)
#endif

/// Code based off Johan Høye's [HOYE2006]. Rewritten in C++ for Ngene with
/// modifications, hopefully making things simpler and faster.
///
/// The gene is a dna sequence that codes a protein. The sequence includes a
/// promoter that a protein recognizes and triggers an action. The translation
/// of this gene is done beforehand to reduce cpu cycles.

#ifndef GENE
#define GENE

#define DIRECTIONS 6

#include "../../../src/Development/Protein.h"
#include "../../../src/Random.h"
#include <algorithm>
#include <boost/dynamic_bitset.hpp>
#include "CellType.h"
#include "Mutable.h"
#include "ProteinType.h"
#include "Setup.h"

class Gene
{
private:
	boost::dynamic_bitset<> sequence;
	const Setup *setup;
	Protein protein;

public:
	Gene(const Setup *s);
	Gene(const Gene &g);

	/// Randomly mutates a property of this gene (and effectively the protein).
	/// Currently, there are no way to check that the mutated values are not
	/// out of bounds. Time will tell whether this is disadvantageous or
	/// beneficial.
	void mutate();

	Gene &operator =(const Gene &gene);
};

#endif
