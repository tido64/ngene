#include <Development/AbstractDevelopment.h>
#include <Development/Organism.h>
#include "Function.h"

class Cartesian : public AbstractDevelopment
{
private:
	const unsigned int bits, l, MAX_CHEMICALS;
	std::vector<unsigned int> nodes, output;
	std::vector<Function *> system;

public:
	Cartesian(const unsigned int t, const unsigned int l);
	~Cartesian();

	// Implements AbstractDevelopment's methods
	void execute(Cell &);
	void initialize(Organism *);
};
