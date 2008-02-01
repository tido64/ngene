/// Nbryo's entry point and face towards Ngene. Produces the random genotypes
/// as well as translating them into phenotypes and equivalent strings for
/// output.

#include "../../../src/Interfaces/Genotype.h"
#include "Synthesizer.h"

namespace Nbryo
{
	Synthesizer synthesizer;
}

using std::string;
using std::vector;

void initiate(const string &parameters) { }

void seed(Genotype &genotype)
{
	DNA dna = Nbryo::synthesizer.synthesize();
	genotype.reserve(dna.size());
	for (DNA::iterator i = dna.begin(); i != dna.end(); i++)
		genotype.push_back(*i);
}

const char *species()
{
	return "Nbryo ";
}

const char *str(const vector<boost::any> &genotype)
{
	return "some string";
}
