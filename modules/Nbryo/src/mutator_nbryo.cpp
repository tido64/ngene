#include "../../../src/Interfaces/Mutator.h"
#include "Gene.h"

namespace Nbryo
{
	Random mt_rand;
}

void initiate(const char *parameters) { }

void mutate(Genotype &genotype)
{
	if (Nbryo::mt_rand.next() < 0.5) // duplicate or delete gene
	{
		if (Nbryo::mt_rand.next() < 0.7) // duplicate
			genotype.push_back(genotype[Nbryo::mt_rand.next_int(genotype.size())]);
		else if (genotype.size() > 1) // erase
			genotype.erase(genotype.begin() + Nbryo::mt_rand.next_int(genotype.size()));
	}
	else // mutate a random property
		boost::unsafe_any_cast<Gene>(&genotype[0])->mutate();
}

const char *name()
{
	return "Nbryo genome mutator";
}
