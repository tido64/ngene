#ifndef PROTEIN
#define PROTEIN

#include <vector>

struct Protein
{
	int life, meta, type;
	std::vector<int> neighbourhood_criteria;
	std::vector<double> chemical_criteria, parameters;
};

#endif
