/// Code based off Johan Høye's [HOYE2006]. Rewritten in C++ for Ngene with
/// modifications, hopefully making things simpler and faster.

#ifndef PROTEIN
#define PROTEIN

#include <vector>
#include <boost/dynamic_bitset.hpp>
#include "ProteinType.h"

class Cell;

class Protein
{
public:
	const ProteinType::Type type;			///< The type this protein belongs to
	const std::vector<double> parameters;	///< The parameters the protein can effect the host cell

	Protein(const Gene *gene)
		: type(gene->protein_type), parameters(gene->protein_parameters), lifespan(gene->protein_lifespan), thresholds(gene->protein_thresholds), neighbours(gene->protein_neighbours), promoter(gene->protein_promoter)
	{ }

	virtual ~Protein() { }

	/// Ages the protein and checks whether it died or not.
	bool age()
	{
		return --this->lifespan < 0 ? true : false;
	}

	/// Checks whether the dna sequence contains the promoter.
	bool find_promoter(const boost::dynamic_bitset<> *sequence)
	{
		return this->promoter.is_subset_of(*sequence);
	}

	/// Checks whether this protein is activated given current states
	virtual bool is_active();

	/// Makes the protein aware of its host.
	void make_aware(const Cell *host)
	{
		this->host = host;
	}

private:
	unsigned int lifespan;							///< The number of ticks left for this protein to live
	const boost::dynamic_bitset<> promoter;			///< The promoter this protein will respond to
	const std::vector<double> thresholds;			///< The thresholds at which this protein will be activated
	const std::vector<CellType::Type> neighbours;	///< The criteria for a thriving neighbourhood
	const Cell *host;								///< The cell hosting the protein
};

#endif
