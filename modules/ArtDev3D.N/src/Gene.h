#if defined( WIN32) && defined(_DEBUG)
#pragma warning(disable: 4267)
#endif

/// Code based off Johan Høye's [HOYE2006]. Rewritten in C++ for Ngene with
/// modifications, hopefully making things simpler and faster.
///
/// The gene is a dna sequence that codes a protein. The sequence includes a
/// promoter that a protein recognizes and triggers the transcription. The
/// translation of a gene is done beforehand to reduce cpu cycles.

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
	boost::dynamic_bitset<> sequence;	///< The DNA sequence of this gene
	const Setup *setup;					///< Parameters the mutation abides by
	Protein protein;					///< The protein this gene translates into

public:
	/// Creates a gene with random properties.
	Gene(const Setup *s);

	/// Duplicates the given gene.
	Gene(const Gene &g);

	/// Randomly mutates a property of this gene (and effectively the protein).
	/// Currently, the mutated values for chemical criteria are not bounds
	/// checked.
	void mutate();

	Gene &operator =(const Gene &gene);
};

#endif
