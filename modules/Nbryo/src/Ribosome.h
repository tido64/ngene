/// Code based off Johan Høye's [HOYE2006]. Rewritten in C++ for Ngene with
/// modifications, hopefully making things simpler and faster.
///
/// Ribosome is the proper name for a "protein factory".

#ifndef RIBOSOME
#define RIBOSOME

#include "Gene.h"
#include "Protein_Adjusting.h"
#include "Protein_Division.h"
#include "Protein_Speciation.h"
#include "Protein_Transcribing.h"

class Ribosome
{
public:
	Ribosome();

	/// The ribosome translates an mRNA and generates a polypeptide chain.
	/// While simulating it, transcribing DNA to mRNA is not necessary so it is
	/// skipped. The ribosome instead translates the DNA directly.
	Protein *translate(std::vector<Gene>::const_iterator gene);
};

#endif
