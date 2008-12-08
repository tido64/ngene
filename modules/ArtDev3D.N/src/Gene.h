#if defined( WIN32) && defined(_DEBUG)
#	pragma warning(disable: 4267)
#endif

/// Code based off Johan Høye's [HOYE2006]. Rewritten in C++ for Ngene with
/// modifications, hopefully making things simpler and faster.
///
/// The gene is a dna sequence that codes a protein. The sequence includes a
/// promoter that a protein recognizes and triggers the transcription. The
/// translation of a gene is done beforehand to reduce cpu cycles.

#ifndef GENE_H_
#define GENE_H_

#define DIRECTIONS 6

#include <algorithm>

#include <Algorithm.h>
#include <Random.h>
#include <Development/Protein.h>

#include "CellType.h"
#include "Mutable.h"
#include "ProteinType.h"
#include "Setup.h"

class Gene
{
public:
	const Setup *setup;		///< Parameters the mutation abides by

	/// Creates a gene with random properties.
	Gene(const Setup *s, Random *r);

	/// Duplicates the given gene.
	Gene(const Gene &g);

	/// Returns a constant pointer to the protein.
	const Protein *get_protein();

	/// Returns the dna sequence of this gene.
	unsigned int get_sequence();

	/// Randomly mutates a property of this gene (and effectively the protein).
	/// Currently, the mutated values for chemical criteria are not bounds
	/// checked.
	void mutate();

private:
	unsigned int sequence;	///< The DNA sequence of this gene
	Random *random;			///< Random number generator
	Protein protein;		///< The protein this gene translates into
};

#endif
