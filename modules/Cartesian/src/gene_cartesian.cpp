#include "../../../src/Interfaces/Genotype.h"
#include "Cartesian.h"

namespace cgp
{
	unsigned int inputs, levels, ticks;
	std::string name ("Cartesian");
	Cartesian *sys;
}

void initiate(const char *parameters)
{
	std::stringstream ss (parameters);
	ss >> cgp::ticks >> cgp::levels >> cgp::inputs;

	cgp::name += " (t=";
	cgp::name += ngene::to_string<int>(cgp::ticks);
	cgp::name += ", l=";
	cgp::name += ngene::to_string<int>(cgp::levels);
	cgp::name += ", n=";
	cgp::name += ngene::to_string<int>(cgp::inputs);
	cgp::name += ')';

	cgp::sys = new Cartesian(cgp::ticks, cgp::levels, cgp::inputs);
}

void phenotype(boost::any &phenotype, const Genotype &genotype)
{
	cgp::sys->evolve(genotype);
	phenotype = cgp::sys->get_organism();
}

void seed(Genotype &genotype)
{
}

const char *species()
{
	return cgp::name.c_str();
}

const char *str(const Genotype &genotype)
{
	delete cgp::sys;
	return '\0';
}
