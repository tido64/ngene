#include <Mutator.h>
#include "Gene.h"

void initiate(const char *parameters) { }

void mutate(Genotype &genotype)
{
	int idx = ngene::random->next_int(genotype.size());
	if (ngene::random->next() < 0.5) // duplicate or delete gene
	{
		if (ngene::random->next() < 0.7) // duplicate
			genotype.push_back(genotype[idx]);
		else if (genotype.size() > 1) // erase
			genotype.erase(genotype.begin() + idx);
	}
	else // mutate a random property
		boost::unsafe_any_cast<Gene>(&genotype[idx])->mutate();
		//genotype[idx].cast<Gene>()->mutate();
}

const char *name()
{
	return "ArtDev3D.N genome mutator";
}
