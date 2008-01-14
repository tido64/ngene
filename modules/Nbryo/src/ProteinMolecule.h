/// Code based off Johan Høye's [HOYE2006]. Rewritten in C++ for Ngene with
/// modifications, hopefully making things simpler and faster.

#ifndef PROTEINMOLECULE
#define PROTEINMOLECULE

#include <vector>
#include "ProteinType.h"

class Cell;

class ProteinMolecule
{
public:
	const ProteinType::Type type;			///< The type this protein belongs to

	ProteinMolecule(const ProteinType::Type type,
		const std::vector<double> *thresholds,
		unsigned int lifespan,
		const std::vector<double> *parameters)
		: type(type), thresholds(thresholds), lifespan(lifespan), parameters(parameters) { };
	virtual ~ProteinMolecule() { };

	/// Ages the protein and checks whether it died or not.
	bool age() { return --this->lifespan < 0 ? true : false; }

	/// Checks whether this protein is activated given current states
	virtual bool is_active();

	void make_aware(Cell *host) { this->host = host; }

	virtual void perform_action() = 0;

protected:
	Cell *host;								///< The cell hosting the protein
	const std::vector<double> *parameters,	///< The parameters the protein can effect the host cell
		*thresholds;						///< The thresholds at which this protein will be activated

private:
	unsigned int lifespan;					///< The number of ticks left for this protein to live
};

#include "Cell.h"

#endif
