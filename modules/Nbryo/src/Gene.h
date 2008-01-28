/// Code based off Johan Høye's [HOYE2006]. Rewritten in C++ for Ngene with
/// modifications, hopefully making things simpler and faster.

#ifndef GENE
#define GENE

#include <string>
#include <boost/dynamic_bitset.hpp>
#include "ProteinType.h"

class Gene
{
public:
	Gene() { };

	Gene(
		const boost::dynamic_bitset<> &sequence,
		const ProteinType::Type protein_type,
		const unsigned int protein_lifespan,
		const std::vector<double> &protein_thresholds,
		const boost::dynamic_bitset<> &protein_promoter)
		: sequence(sequence), protein_type(protein_type), protein_lifespan(protein_lifespan), protein_promoter(protein_promoter), protein_thresholds(protein_thresholds) { }

	Gene(
		const boost::dynamic_bitset<> &sequence,
		const ProteinType::Type protein_type,
		const unsigned int protein_lifespan,
		const std::vector<double> &protein_thresholds,
		const std::vector<double> &protein_parameters)
		: sequence(sequence), protein_type(protein_type), protein_lifespan(protein_lifespan), protein_thresholds(protein_thresholds), protein_parameters(protein_parameters) { }

	/// Returns the lifespan (number of ticks) the translated protein will live
	unsigned int get_protein_lifespan() const;

	/// Returns the parameters of the translated protein
	const std::vector<double> *get_protein_parameters() const;

	/// Returns the promoter that the translated protein will respond to
	const boost::dynamic_bitset<> *get_protein_promoter() const;

	/// Returns the type of the translated protein
	ProteinType::Type get_protein_type() const;

	/// Returns the dna sequence of this gene.
	const boost::dynamic_bitset<> *get_sequence() const;

	/// Returns the pointer to the thresholds the translated protein will abide by
	const std::vector<double> *get_protein_thresholds() const;

	/// Randomly mutates a property of this gene (effectively the protein).
	void mutate();

	void operator=(const Gene &gene);

private:
	boost::dynamic_bitset<> sequence;			///< The dna sequence with a promoter

	// Protein related code
	ProteinType::Type protein_type;				///< The translated protein's type
	unsigned int protein_lifespan;				///< The translated protein's lifespan
	boost::dynamic_bitset<> protein_promoter;	///< The translated protein's promoter
	std::vector<double> protein_thresholds;		///< The translated protein's hormonal thresholds
	std::vector<double> protein_parameters;		///< The translated protein's parameters
};

#endif
