// FIXME: Even with the output nodes correctly crossed, they can point to invalid addresses!

#include <algorithm>
#include "../../../src/Interfaces/Mating.h"
#include "Function.h"

namespace cgp
{
	const unsigned int output_nodes = 10;
	std::string name ("Cartesian (single-point)");
}

void initiate(const char *parameters) { }

void mate(std::vector<Specimen> &children, const Specimen &parentA, const Specimen &parentB)
{
	const unsigned int lower = (parentA.genotype.size() < parentB.genotype.size())
		? parentA.genotype.size() - 1 : parentB.genotype.size() - 1;
	unsigned int split = ngene::random->next_int(lower);

	children[0].genotype.reserve(parentB.genotype.size());
	children[1].genotype.reserve(parentA.genotype.size());

	if (split > lower - cgp::output_nodes)
	{
		split = lower - split;
		for (Genotype::const_reverse_iterator i = parentA.genotype.rbegin(); i != parentA.genotype.rbegin() + split; i++)
			children[0].genotype.push_back(*i);
		for (Genotype::const_reverse_iterator i = parentB.genotype.rbegin() + split; i != parentB.genotype.rend(); i++)
			children[0].genotype.push_back(*i);
		for (Genotype::const_reverse_iterator i = parentB.genotype.rbegin(); i != parentB.genotype.rbegin() + split; i++)
			children[1].genotype.push_back(*i);
		for (Genotype::const_reverse_iterator i = parentA.genotype.rbegin() + split; i != parentA.genotype.rend(); i++)
			children[1].genotype.push_back(*i);
		std::reverse(children[0].genotype.begin(), children[0].genotype.end());
		std::reverse(children[1].genotype.begin(), children[1].genotype.end());
	}
	else
	{
		children[0].genotype.assign(parentA.genotype.begin(), parentA.genotype.begin() + split);
		children[0].genotype.insert(children[0].genotype.end(), parentB.genotype.begin() + split, parentB.genotype.end());
		children[1].genotype.assign(parentB.genotype.begin(), parentB.genotype.begin() + split);
		children[1].genotype.insert(children[1].genotype.end(), parentA.genotype.begin() + split, parentA.genotype.end());
	}

	// debug
	printf("==> Parent A:");
	for (Genotype::const_iterator i = parentA.genotype.begin(); i != parentA.genotype.end(); i++)
		printf(" %u", boost::any_cast<unsigned int>(*i));
	printf("\n==> Parent B:");
	for (Genotype::const_iterator i = parentB.genotype.begin(); i != parentB.genotype.end(); i++)
		printf(" %u", boost::any_cast<unsigned int>(*i));
	printf("\n==> Child 0:");
	for (Genotype::iterator i = children[0].genotype.begin(); i!= children[0].genotype.end(); i++)
		printf(" %u", boost::any_cast<unsigned int>(*i));
	printf("\n==> Child 1:");
	for (Genotype::iterator i = children[1].genotype.begin(); i!= children[1].genotype.end(); i++)
		printf(" %u", boost::any_cast<unsigned int>(*i));
	printf("\n");
}

const char *name()
{
	return cgp::name.c_str();
}

const unsigned int MATING_INTERFACE offspring()
{
	return 2;
}
