#include "../../../src/Interfaces/Mutator.h"
#include "../../../src/Random.h"
#include "Function.h"

namespace cgp
{
	std::string name ("Cartesian");
}

void initiate(const char *parameters) { }

void mutate(Genotype &genotype)
{
	int address = Random::Instance().next_int(genotype.size());
	if (address % 4 == 3) // change function adress
		genotype[address] = Random::Instance().next_int(NUMBER_OF_FUNCTIONS);
	else // change input adress
	{
		int in = *boost::unsafe_any_cast<int>(&genotype[address]);
		in -= Random::Instance().next_int(1, in);
		genotype[address] = in;
	}
}

const char *name()
{
	return cgp::name.c_str();
}
