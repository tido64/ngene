#include "../../../src/Interfaces/Genotype.h"
#include <algorithm>
#include <sstream>

#include "ArtDev3D.h"
//#include "Synthesizer.h"

namespace N
{
	unsigned int ticks;
	std::string name;
	Coordinates boundaries;
//	Synthesizer synthesizer;
	ArtDev3D artdev3d;
}

using std::map;
using std::string;
using std::stringstream;
using std::vector;

void initiate(const char *parameters)
{
	//stringstream in (parameters);
	//in >> n::ticks >> n::boundaries.x >> n::boundaries.y >> n::boundaries.z;
	//n::name = "artdev3d.n (development time=";
	//n::name += parameters;
	//n::name += ')';
}

void phenotype(boost::any &phenotype, const Genotype &genotype)
{
	//DNA dna;
	//for (Genotype::const_iterator i = genotype.begin(); i != genotype.end(); i++)
	//	dna.push_back(boost::any_cast<Gene>(*i));

	//Organism o (dna, N::boundaries);
	//for (unsigned int i = 0; i < N::ticks; i++)
	//	o.increment_tick();

	//phenotype = o.get_phenotype();
}

void seed(vector<boost::any> &genotype)
{
	//N::synthesizer.synthesize(genotype);
}

const char *species()
{
	return N::name.c_str();
}

const char *str(const Genotype &genotype)
{
	N::artdev3d.evolve(genotype);
	return N::artdev3d.to_string();
}
