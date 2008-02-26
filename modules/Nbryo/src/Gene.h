/// Code based off Johan Høye's [HOYE2006]. Rewritten in C++ for Ngene with
/// modifications, hopefully making things simpler and faster.
///
/// The gene is a dna sequence that codes a protein. The sequence includes a
/// promoter that a protein recognizes and triggers an action. The translation
/// of this gene is done beforehand to reduce cpu cycles.

#ifndef GENE
#define GENE

#include <boost/dynamic_bitset.hpp>
#include "CellType.h"
#include "Direction.h"
#include "Mutable.h"
#include "ProteinType.h"
#include "../../../src/Random.h"

class Gene
{
	friend class Protein;

public:
	/// This constructor is required by boost::any. See Concept CopyConstructible.
	Gene(const Gene &);

	Gene(
		const boost::dynamic_bitset<> &sequence,
		const ProteinType::Type protein_type,
		const unsigned int protein_lifespan,
		const std::vector<double> &protein_thresholds,
		const std::vector<CellType::Type> &protein_neighbourhood,
		const unsigned int number_of_cell_type);

	/// Sets the protein promoter as well as the number of cell types it can
	/// be used to transcribe.
	void ergo_proxy(const boost::dynamic_bitset<> &protein_promoter);

	/// Sets the protein parameters and the upper and lower boundaries of each
	/// parameter.
	void ergo_proxy(const std::vector<double> &protein_parameters, const std::pair<double, double> *stimuli_boundaries);

	/// Returns the dna sequence of this gene.
	const boost::dynamic_bitset<> &get_sequence() const;

	/// Randomly mutates a property of this gene (and effectively the protein).
	/// Currently, there are no way to check that the mutated values are not
	/// out of bounds. Time will tell whether this is disadvantageous or
	/// beneficial.
	void mutate();

	Gene &operator =(const Gene &gene);

private:
	boost::dynamic_bitset<> sequence;					///< The dna sequence with a promoter

	// Protein related code
	ProteinType::Type protein_type;						///< The translated protein's type
	unsigned int protein_lifespan;						///< The translated protein's lifespan
	boost::dynamic_bitset<> protein_promoter;			///< The translated protein's promoter
	std::vector<double> protein_thresholds;				///< The translated protein's hormonal thresholds
	std::vector<CellType::Type> protein_neighbourhood;	///< The translated protein's criteria for a thriving neighbourhood
	std::vector<double> protein_parameters;				///< The translated protein's parameters

	// Configuration (for the lack of a more elegant way)
	unsigned int number_of_cell_types;					///< Number of cell types used in current run
	std::pair<double, double> protein_stimuli;			///< Min (first) and max (second) stimulus
};

#endif
