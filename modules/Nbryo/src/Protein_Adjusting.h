/// Code based off Johan Høye's [HOYE2006]. Rewritten in C++ for Ngene with
/// modifications, hopefully making things simpler and faster.

#ifndef PROTEIN_ADJUSTING
#define PROTEIN_ADJUSTING

#include "ProteinMolecule.h"

class Protein_Adjusting : public ProteinMolecule
{
public:
	const double MAX, MIN;
	Protein_Adjusting(const std::vector<double> *thresholds,
		unsigned int lifespan,
		const std::vector<double> *parameters)
		: ProteinMolecule(ProteinType::adjusting, thresholds, lifespan, parameters), MAX(1.0), MIN(-1.0) { };
	void perform_action();
};

#endif
