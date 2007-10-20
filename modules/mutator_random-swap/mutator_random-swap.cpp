#include "mutator_random-swap.h"

void mutate(std::vector<boost::any> &genotype)
{
	std::swap(genotype[(int)(rand() / (RAND_MAX + 1.0) * genotype.size())],
		genotype[(int)(rand() / (RAND_MAX + 1.0) * genotype.size())]);
}

