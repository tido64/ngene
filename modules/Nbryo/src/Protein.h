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

	Protein(
		const ProteinType::Type type,
		unsigned int lifespan,
		const std::vector<double> *thresholds,
		const boost::dynamic_bitset<> *promoter)
		: type(type), lifespan(lifespan), thresholds(*thresholds), promoter(*promoter) { }

	Protein(
		const ProteinType::Type type,
		unsigned int lifespan,
		const std::vector<double> *thresholds,
		const std::vector<double> *parameters)
		: type(type), lifespan(lifespan), thresholds(*thresholds), parameters(*parameters) { }

	virtual ~Protein() { }

	/// Ages the protein and checks whether it died or not.
	bool age()
	{
		return --this->lifespan < 0 ? true : false;
	}

	bool find_promoter(const boost::dynamic_bitset<> *sequence)
	{
		return this->promoter.is_subset_of(*sequence);
	}

	/// Checks whether this protein is activated given current states
	virtual bool is_active();

	/// Makes the protein aware of its host.
	void make_aware(Cell *host)
	{
		this->host = host;
	}

private:
	unsigned int lifespan;					///< The number of ticks left for this protein to live
	const boost::dynamic_bitset<> promoter;	///< The promoter this protein will respond to
	const std::vector<double> thresholds;	///< The thresholds at which this protein will be activated
	Cell *host;								///< The cell hosting the protein
};

#endif
