/// Code based off Johan Høye's [HOYE2006]. Rewritten in C++ for Ngene with
/// modifications, hopefully making things simpler and faster.

#ifndef PROTEIN_DIVISION
#define PROTEIN_DIVISION

#include "ProteinMolecule.h"

class Protein_Division : public ProteinMolecule
{
public:
	const double MAX, MIN;
	Protein_Division(const std::vector<double> *thresholds,
		unsigned int lifespan,
		const std::vector<double> *parameters)
		: ProteinMolecule(ProteinType::division, thresholds, lifespan, parameters), MAX(1.0), MIN(-1.0) { };
	void perform_action();
};

#endif
