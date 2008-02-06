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
	Protein(const Gene *gene);

	virtual ~Protein() { }

	/// Ages the protein and checks whether it died or not.
	bool age();

	/// Checks whether the dna sequence contains the promoter.
	bool find_promoter(const boost::dynamic_bitset<> *sequence);

	const std::vector<double> *get_parameters();

	ProteinType::Type get_type();

	/// Checks whether this protein is activated given current states
	virtual bool is_active();

	/// Makes the protein aware of its host.
	void make_aware(const Cell *host);

	void operator =(const Protein &p);

private:
	ProteinType::Type type;						///< The type this protein belongs to
	unsigned int lifespan;						///< The number of ticks left for this protein to live
	boost::dynamic_bitset<> promoter;			///< The promoter this protein will respond to
	std::vector<double> thresholds;				///< The thresholds at which this protein will be activated
	std::vector<CellType::Type> neighbourhood;	///< The criteria for a thriving neighbourhood
	std::vector<double> parameters;				///< The parameters the protein can effect the host cell
	const Cell *host;							///< The cell hosting the protein
};

#endif
