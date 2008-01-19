/// Code based off Johan Høye's [HOYE2006]. Rewritten in C++ for Ngene with
/// modifications, hopefully making things simpler and faster.

#ifndef PROTEIN_ADJUSTING
#define PROTEIN_ADJUSTING

#include "Protein.h"

class Protein_Adjusting : public Protein
{
public:
	const double MAX, MIN;
	Protein_Adjusting(const std::vector<double> *thresholds,
		unsigned int lifespan,
		const std::vector<double> *parameters)
		: Protein(thresholds, lifespan, parameters, ProteinType::adjusting), MAX(1.0), MIN(-1.0) { };
	void perform_action();
};

#endif
