/// Nbryo's entry point and face towards Ngene. Produces the random genotypes
/// as well as translating them into phenotypes and equivalent strings for
/// output.

#include <sstream>
#include "../../../src/Interfaces/Genotype.h"
#include "Synthesizer.h"

namespace Nbryo
{
	unsigned int ticks;
	Coordinates boundaries;
	Synthesizer *synthesizer;
	std::string name;
}

using std::map;
using std::string;
using std::stringstream;
using std::vector;

void initiate(const char *parameters)
{
	stringstream in (parameters);
	in >> Nbryo::ticks >> Nbryo::boundaries.x >> Nbryo::boundaries.y >> Nbryo::boundaries.z;
	Nbryo::name = "Nbryo (development time=";
	Nbryo::name += parameters;
	Nbryo::name += ')';
	Nbryo::synthesizer = new Synthesizer();
}

void phenotype(boost::any &phenotype, const Genotype &genotype)
{
	DNA dna;
	for (Genotype::const_iterator i = genotype.begin(); i != genotype.end(); i++)
		dna.push_back(boost::any_cast<Gene>(*i));

	Organism o (dna, Nbryo::boundaries);
	for (unsigned int i = 0; i < Nbryo::ticks; i++)
		o.increment_tick();

	phenotype = o.get_phenotype();
}

void seed(Genotype &genotype)
{
	Nbryo::synthesizer->synthesize(genotype);
}

const char *species()
{
	return Nbryo::name.c_str();
}

const char *str(const Genotype &genotype)
{
	boost::any phenotype_container;
	phenotype(phenotype_container, genotype);
	map<Coordinates, CellType::Type>
		organism (*boost::unsafe_any_cast<map<Coordinates, CellType::Type> >(&phenotype_container));

	stringstream o;
	for (map<Coordinates, CellType::Type>::const_iterator i = organism.begin(); i != organism.end(); i++)
		o << i->first.x << " " << i->first.y << " " << i->first.z << " " << i->second << "\n";
	Nbryo::name = o.str();

	delete Nbryo::synthesizer;
	return Nbryo::name.c_str();
}
