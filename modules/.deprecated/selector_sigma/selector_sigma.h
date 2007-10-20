#include "../../Ngene/Interfaces/Selector.h"
#include <cmath>

namespace Sigma
{
	std::vector<double> roulette;
	double random() { return (double)rand() / ((double)RAND_MAX + 1.0); }
}

const char *name() { return "Sigma Scaling"; }
