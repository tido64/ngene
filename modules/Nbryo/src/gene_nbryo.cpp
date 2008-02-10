/// Nbryo's entry point and face towards Ngene. Produces the random genotypes
/// as well as translating them into phenotypes and equivalent strings for
/// output.

#include <sstream>
#include "../../../src/Interfaces/Genotype.h"
#include "Synthesizer.h"

namespace Nbryo
{
	unsigned int ticks;
	Synthesizer *synthesizer;
	std::string name;
}

using std::map;
using std::string;
using std::stringstream;
using std::vector;

void initiate(const char *parameters)
{
	Nbryo::ticks = atoi(parameters);
	Nbryo::name = "Nbryo (development time=";
	Nbryo::name += parameters;
	Nbryo::name += ')':
	Nbryo::synthesizer = new Synthesizer();
}

const void *phenotype(const Genotype &genotype)
{
	vector<Gene> dna;
	for (Genotype::const_iterator i = genotype.begin(); i != genotype.end(); i++)
		dna.push_back(boost::any_cast<Gene>(*i));

	Organism o (dna);
	for (unsigned int i = 0; i < Nbryo::ticks; i++)
		o.increment_tick();

	return o.phenotype();
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
	const map<Coordinates, CellType::Type> *organism
		= (const map<Coordinates, CellType::Type> *)phenotype(genotype);

	stringstream o;
	for (map<Coordinates, CellType::Type>::const_iterator i = organism->begin(); i != organism->end(); i++)
		o << i->first.x << " " << i->first.y << " " << i->first.z << " " << i->second << "\n";
	Nbryo::name = o.str();

	delete organism;
	delete Nbryo::synthesizer;
	return Nbryo::name.c_str();
}
