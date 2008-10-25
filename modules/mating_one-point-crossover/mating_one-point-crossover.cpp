#include "../../src/Interfaces/Mating.h"

void initiate(const char *parameters) { }

void mate(std::vector<Specimen> &children, const Specimen &parentA, const Specimen &parentB)
{
	unsigned int split = ngene::random->next_int((parentA.genotype.size() < parentB.genotype.size())
		? parentA.genotype.size() - 1 : parentB.genotype.size() - 1) + 1;

	children[0].genotype.reserve(parentB.genotype.size());
	children[0].genotype.assign(parentA.genotype.begin(), parentA.genotype.begin() + split);
	children[0].genotype.insert(children[0].genotype.end(), parentB.genotype.begin() + split, parentB.genotype.end());

	children[1].genotype.reserve(parentA.genotype.size());
	children[1].genotype.assign(parentB.genotype.begin(), parentB.genotype.begin() + split);
	children[1].genotype.insert(children[1].genotype.end(), parentA.genotype.begin() + split, parentA.genotype.end());
}

const char *name()
{
	return "One-point crossover";
}

const unsigned int offspring()
{
	return 2;
}
