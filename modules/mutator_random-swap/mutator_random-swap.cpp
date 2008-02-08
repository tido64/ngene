#include "../../src/Interfaces/Mutator.h"

using std::string;
using std::swap;
using std::vector;

void initiate(const char *parameters) { }

const char *name()
{
	return "Random Swap";
}

void mutate(vector<boost::any> &genotype)
{
	swap(genotype[(int)(rand() / (RAND_MAX + 1.0) * genotype.size())],
		genotype[(int)(rand() / (RAND_MAX + 1.0) * genotype.size())]);
}

