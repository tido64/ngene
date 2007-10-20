#include "../../Ngene/Interfaces/Selector.h"

namespace FitnessProportionate
{
	std::vector<double> roulette;
	double random() { return (double)rand() / ((double)RAND_MAX + 1.0); }
}

const char *name() { return "Fitness Proportionate"; }
