#include "../../src/Interfaces/Mating.h"

void initiate(const std::string &parameters) { }

void mate(std::vector<Specimen> &children, const Specimen &parentA, const Specimen &parentB)
{
	int size, split;

	if (parentB.genotype.size() > parentA.genotype.size())
		size = (int)parentA.genotype.size() - 1;
	else
		size = (int)parentB.genotype.size() - 1;
	do
	{
		split = (int)(size * (double)rand() / ((double)RAND_MAX + 1.0));
	} while (split == 0);

	children[0].genotype = parentB.genotype;
	children[1].genotype = parentA.genotype;
	for (int i = 0; i < split; i++)
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
