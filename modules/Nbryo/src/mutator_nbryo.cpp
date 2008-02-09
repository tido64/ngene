#include "../../../src/Interfaces/Mutator.h"
#include "Gene.h"

void initiate(const char *parameters) { }

void mutate(Genotype &genotype)
{
	if (NUtility::random() < 0.5) // duplicate or delete gene
	{
		if (NUtility::random() < 0.7) // duplicate
			genotype.push_back(boost::any_cast<Gene>(genotype[NUtility::random(genotype.size())]));
		else if (genotype.size() > 1) // erase
			genotype.erase(genotype.begin() + NUtility::random(genotype.size()));
	}
	else // mutate a random property
		(boost::any_cast<Gene>(genotype[NUtility::random(genotype.size())])).mutate();
}

const char *name()
{
	return "Nbryo genome mutator";
}
