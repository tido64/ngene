#include "../../src/Interfaces/Selector.h"

#include <cmath>
#include <cstdlib>
#include <sstream>

namespace tournament
{
	std::string name;
	unsigned int k;
	double p;
	double random() { return (double)rand() / ((double)RAND_MAX + 1.0); }
}

