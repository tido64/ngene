#include "../../src/Interfaces/Mating.h"
#include "../../src/Random.h"

Random mt_rand;

void initiate(const char *parameters) { }

void mate(std::vector<Specimen> &children, const Specimen &parentA, const Specimen &parentB)
{
	unsigned int
		size = (parentB.genotype.size() > parentA.genotype.size() ? parentA.genotype.size() : parentB.genotype.size()) - 1,
		split = mt_rand.next_int(size);

	while (split == 0)
		split = mt_rand.next_int(size);

	children[0].genotype = parentB.genotype;
	children[1].genotype = parentA.genotype;
	for (unsigned int i = 0; i < split; i++)
	{
		children[0].genotype[i] = parentA.genotype[i];
		children[1].genotype[i] = parentB.genotype[i];
	}
}

const char *name()
{
	return "One-point Crossover";
}

const int offspring()
{
	return 2;
}
