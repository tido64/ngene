/// Nbryo's entry point and face towards Ngene. Produces the random genotypes
/// as well as translating them into phenotypes and equivalent strings for
/// output.

#include "../../../src/Interfaces/Genotype.h"
#include "Synthesizer.h"

namespace Nbryo
{
	unsigned int ticks;
	Synthesizer *synthesizer;
	std::string name;
}

using std::string;
using std::vector;

void initiate(const char *parameters)
{
	Nbryo::ticks = atoi(parameters);
	Nbryo::name = "Nbryo ";
	Nbryo::name += parameters;
	Nbryo::synthesizer = new Synthesizer();
}

void *phenotype(const Genotype &genotype)
{
	vector<Gene> dna;
	for (Genotype::const_iterator i = genotype.begin(); i != genotype.end(); i++)
		dna.push_back(boost::any_cast<Gene>(*i));

	Organism *o = new Organism(dna);

	for (unsigned int i = 0; i < Nbryo::ticks; i++)
		o->increment_tick();

	return o;
}

void seed(Genotype &genotype)
{
	DNA dna = Nbryo::synthesizer->synthesize();
	for (DNA::const_iterator i = dna.begin(); i != dna.end(); i++)
		genotype.push_back(*i);
}

const char *species()
{
	return Nbryo::name.c_str();
}

const char *str(const Genotype &genotype)
{
	Organism *o = (Organism *)phenotype(genotype);
	return o->str();
}
