/// Code based off Johan Høye's [HOYE2006]. Rewritten in C++ for Ngene with
/// modifications, hopefully making things simpler and faster.

#ifndef PROTEIN_TRANSCRIBING
#define PROTEIN_TRANSCRIBING

#include "Protein.h"

class Protein_Transcribing : public Protein
{
public:
	const double MAX, MIN;
	Protein_Transcribing(const std::vector<double> *thresholds,
		unsigned int lifespan,
		const std::vector<double> *parameters)
		: Protein(ProteinType::adjusting, thresholds, lifespan, parameters), MAX(1.0), MIN(-1.0) { };
	void perform_action();
};

#endif
