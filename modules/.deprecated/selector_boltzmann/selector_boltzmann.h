#include "../../Ngene/Interfaces/Selector.h"
#include <cmath>
#include <sstream>

namespace Boltzmann
{
	double T;
	std::string name;
	std::vector<double> roulette;
	double random() { return (double)rand() / ((double)RAND_MAX + 1.0); }
}
