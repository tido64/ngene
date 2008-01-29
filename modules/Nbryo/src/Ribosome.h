/// Code based off Johan Høye's [HOYE2006]. Rewritten in C++ for Ngene with
/// modifications, hopefully making things simpler and faster.
///
/// Ribosome is the proper name for a "protein factory".

#ifndef RIBOSOME
#define RIBOSOME

#include "Cell.h"

class Ribosome
{
public:
	Ribosome(Cell *host) : host(host) { };

	/// The ribosome translates an mRNA and generates a polypeptide chain.
	/// While simulating it, transcribing DNA to mRNA is not necessary so it is
	/// skipped. The ribosome instead translates the DNA directly.
	Protein *translate(const Gene *gene);

private:
	Cell *host;
};

#endif
