#include "../../../src/Development/AbstractDevelopment.h"
#include "../../../src/Development/Organism.h"
#include "Functions.h"

class Cartesian : public AbstractDevelopment
{
private:
	std::vector<unsigned int> system;

public:
	Cartesian(int t = 10) : AbstractDevelopment(t) { }
	double diffuse(const double lvl, const std::vector<Message> &in);

	// Implements AbstractDevelopment's methods
	void execute(Cell &);
	void initialize(Organism *);
};
