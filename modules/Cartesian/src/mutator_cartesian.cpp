#include <Mutator.h>
#include "Function.h"

namespace cgp
{
	std::string name ("Cartesian");
}

void initiate(const char *parameters) { }

void mutate(Genotype &genotype)
{
	unsigned int address = ngene::random->next_int(genotype.size());
	if (address % 4 == 3) // change function adress
		genotype[address] = ngene::random->next_int(NUMBER_OF_FUNCTIONS);
	else // change input adress
		genotype[address] = ngene::random->next_int(*boost::unsafe_any_cast<unsigned int>(&genotype[address]));
}

const char *name()
{
	return cgp::name.c_str();
}
