#include "../../../src/Interfaces/Mutator.h"
#include "Gene.h"

void initiate(const char *parameters) { }

void mutate(Genotype &genotype)
{
	if (NUtility::random() < 0.5) // duplicate or delete gene
	{
		if (NUtility::random() < 0.7) // duplicate
			genotype.push_back(genotype[NUtility::random(genotype.size())]);
		else if (genotype.size() > 1) // erase
			genotype.erase(genotype.begin() + NUtility::random(genotype.size()));
	}
	else // mutate a random property
		boost::unsafe_any_cast<Gene>(&genotype[0])->mutate();
}

const char *name()
{
	return "Nbryo genome mutator";
}
