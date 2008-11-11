#include "../../../src/Interfaces/Genotype.h"
#include "Cartesian.h"

namespace cgp
{
	unsigned int levels, nodes, ticks, width, height;
	std::string name ("Cartesian");
	Cartesian *sys;
}

void initiate(const char *parameters)
{
	std::stringstream ss (parameters);
	ss >> cgp::ticks >> cgp::levels >> cgp::nodes >> cgp::width >> cgp::height;

	cgp::name += " (t=";
	cgp::name += ngene::to_string<unsigned int>(cgp::ticks);
	cgp::name += ", l=";
	cgp::name += ngene::to_string<unsigned int>(cgp::levels);
	cgp::name += ", n=";
	cgp::name += ngene::to_string<unsigned int>(cgp::nodes);
	cgp::name += ')';

	cgp::sys = new Cartesian(cgp::ticks, cgp::levels);
}

void phenotype(boost::any &phenotype, const Genotype &genotype)
{
	cgp::sys->evolve(genotype);
	phenotype = cgp::sys->get_organism();
}

void seed(Genotype &genotype)
{
	/**
	* Input:
	* - 9 ints for chemical levels
	* - 9 ints for cell types
	*
	* Output:
	* - 1 int for cell type
	* - 1 int for cell growth
	* - 8 ints for chemical levels
	*
	* All ints are unsigned
	**/
	const unsigned int
		input = 18,
		output = 10;

	unsigned int lower = 0, upper = input;
	std::vector<unsigned int> layer;
	layer.reserve(cgp::levels + 1);

	if (cgp::nodes < 1)
	{
		layer.push_back(ngene::random->next_int(input));
		for (unsigned int i = 1; i < cgp::levels; i++)
			layer.push_back(ngene::random->next_int(layer.back()));
	}
	else
		for (unsigned int i = 0; i < cgp::levels; i++)
			layer.push_back(cgp::nodes);

	// Generate working nodes
	for (unsigned int i = 0; i < cgp::levels; i++)
	{
		for (unsigned int j = 0; j < layer[i]; j++)
		{
			genotype.push_back(static_cast<unsigned int>(ngene::random->next_int(lower, upper)));
			genotype.push_back(static_cast<unsigned int>(ngene::random->next_int(lower, upper)));
			genotype.push_back(static_cast<unsigned int>(ngene::random->next_int(lower, upper)));
			genotype.push_back(ngene::random->next_int(NUMBER_OF_FUNCTIONS));
		}
		lower += (i < 2) ? 0 : layer[i - 2];
		upper += layer[i];
	}

	// Specify output nodes
	for (unsigned int i = 0; i < output; i++)
		genotype.push_back(static_cast<unsigned int>(ngene::random->next_int(lower, upper)));
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

	//for (std::map<Coordinates, Cell>::iterator i = o.begin(); i != o.end(); i++)
	//	printf("==> [%d,%d] %d\n", i->first.x, i->first.y, i->second.type);
	//printf("==>\n");

	int
		range_x = cgp::width / 2,
		range_y = cgp::height / 2;
	std::map<Coordinates, Cell>::const_iterator res;
	std::stringstream ss;
	Coordinates slot (-range_x, -range_y);

	for (unsigned int y = 0; y < cgp::height; y++)
	{
		//printf("==>");
		slot.x = -range_x;
		slot.y = y - range_y;
		for (unsigned int x = 0; x < cgp::width; x++)
		{
			res = o.find(slot);
			if (res != o.end())
				//printf("  [%d,%d] %d", slot.x, slot.y, res->second.type);
				ss << res->second.type << " ";
			else
				//printf("  [%d,%d] -", slot.x, slot.y);
				ss << "0 ";
			slot.x++;
		}
		//printf("\n");
		ss << std::endl;
	}
	cgp::name = ss.str();
	return cgp::name.c_str();
}
