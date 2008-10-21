#include "../../../src/Interfaces/Genotype.h"
#include "../../../src/Random.h"
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
	/**
		9 ints for chemical levels (input)
		9 ints for cell types (input)
		--
		1 int for cell type (output)
		1 int for cell growth (output)
		8 ints for chemical levels (output)
	*/
	std::vector<int> nodes;
	nodes.push_back(0);
	nodes.push_back(0);
	nodes.push_back(Random::Instance().next_int(18));
	nodes.push_back(Random::Instance().next_int(nodes[2]));
	nodes.push_back(Random::Instance().next_int(nodes[3]));
	nodes.push_back(Random::Instance().next_int(nodes[4]));

	int lower = 0, upper = 0;
	for (unsigned int i = 2; i != nodes.size(); i++)
	{
		lower += nodes[i - 2];
		upper += nodes[i];
		for (int j = 0; j < nodes[i]; j++)
		{
			genotype.push_back(Random::Instance().next_int(lower, upper));
			genotype.push_back(Random::Instance().next_int(lower, upper));
			genotype.push_back(Random::Instance().next_int(lower, upper));
			genotype.push_back(Random::Instance().next_int(NUMBER_OF_FUNCTIONS));
		}
	}
	for (int i = 0; i < 10; i++)
		genotype.push_back(Random::Instance().next_int(lower, upper));
}

const char *species()
{
	return cgp::name.c_str();
}

const char *str(const Genotype &genotype)
{
	cgp::sys->evolve(genotype);
	std::map<Coordinates, Cell> o (cgp::sys->get_organism());
	delete cgp::sys;

	std::stringstream ss;
	for (std::map<Coordinates, Cell>::const_iterator i = o.begin(); i != o.end(); i++)
		ss << i->first.x << " " << i->first.y << " " << i->first.z << " " << i->second.type << std::endl;

	return ss.str().c_str();;
}
