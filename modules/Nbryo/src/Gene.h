/// Code based off Johan Høye's [HOYE2006]. Rewritten in C++ for Ngene with
/// modifications, hopefully making things simpler and faster.

#ifndef GENE
#define GENE

#include <string>
#include <vector>

#include "ProteinType.h"

class Gene
{
public:
	const ProteinType::Type protein_type;			///< The type of protein this gene codes for
	const int protein_lifespan;						///< The lifespan of the protein this gene translates into
	const std::vector<double> protein_thresholds;	///< The thresholds the protein will respond to

	const std::string sequence;						///< The dna sequence with a promoter
	const std::vector<double> parameters;			///< The parameters the protein will change

	Gene(const ProteinType::Type protein_type, const int protein_lifespan, const std::vector<double> protein_thresholds,
		const std::string sequence, const std::vector<double> &parameters);
};

#endif
