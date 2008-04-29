#include "../../src/Interfaces/Mutator.h"
#include "../../src/Random.h"

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
	swap(
		genotype[Random::Instance().next_int(genotype.size())],
		genotype[Random::Instance().next_int(genotype.size())]);
}
