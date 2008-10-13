#include "../../../src/Development/AbstractDevelopment.h"
#include "../../../src/Development/Organism.h"
#include "Function.h"

class Cartesian : public AbstractDevelopment
{
private:
	const unsigned int l, n;
	std::vector<unsigned int> nodes;
	std::vector<Function *> system;

public:
	Cartesian(const unsigned int t, const unsigned int l, const unsigned int n);
	~Cartesian();

	double diffuse(const double lvl, const std::vector<Message> &in);

	// Implements AbstractDevelopment's methods
	void execute(Cell &);
	void initialize(Organism *);
};
