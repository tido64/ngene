/// Code based off Johan Høye's [HOYE2006]. Rewritten in C++ for Ngene with
/// modifications, hopefully making things simpler and faster.

#ifndef PROTEIN_SPECIATION
#define PROTEIN_SPECIATION

#include "Protein.h"

class Protein_Speciation : public Protein
{
public:
	const double MAX, MIN;
	Protein_Speciation(const std::vector<double> *thresholds,
		unsigned int lifespan,
		const std::vector<double> *parameters)
		: Protein(ProteinType::transcribing, thresholds, lifespan, parameters), MAX(1.0), MIN(-1.0) { };
	void perform_action();
};

#endif
