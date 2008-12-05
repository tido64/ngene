#include <Mutator.h>

using std::string;
using std::swap;
using std::vector;

void initiate(const char *parameters) { }

const char *name()
{
	return "Random Swap";
}

void mutate(Genotype &genotype)
{
	swap(
		genotype[ngene::random->next_int(genotype.size())],
		genotype[ngene::random->next_int(genotype.size())]);
}
