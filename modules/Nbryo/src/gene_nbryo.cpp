/// Nbryo's entry point and face towards Ngene. Produces the random genotypes
/// as well as translating them into phenotypes and equivalent strings for
/// output.

#include "../../../src/Interfaces/GeneFactory.h"
#include "Nbryo.h"

namespace N
{
	Nbryo instance;
}

using std::string;
using std::vector;
using boost::any;

void initiate(const string &parameters)
{
}

void seed(vector<any> &genotype)
{
	DNA dna = N::instance.synthesize();
	genotype.reserve(dna.size());
	for (DNA::iterator i = dna.begin(); i != dna.end(); i++)
		genotype.push_back(*i);
}

const char *species()
{
	return "Nbryo ";
}

const char *str(const vector<any> &genotype)
{
	return "some string";
}
