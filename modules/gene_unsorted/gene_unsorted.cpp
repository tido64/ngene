#include "../../src/Interfaces/Genotype.h"
#include <algorithm>
#include <sstream>

namespace Ngene
{
	unsigned int numbers;
	std::string output, name, phtype;
}

using std::string;
using std::ostringstream;
using std::vector;

void initiate(const char *parameters)
{
	Ngene::numbers = atoi(parameters.c_str());
	Ngene::name = "Unsorted (n = " + parameters;
	Ngene::name += ')';
	Ngene::phtype = "The phenotype passed on okay.\n";
}

void phenotype(boost::any &phtype, const Genotype &gtype)
{
	phtype = Ngene::phtype.c_str();
}

void seed(vector<boost::any> &genotype)
{
	genotype.reserve(Ngene::numbers);
	for (unsigned int i = 0; i < genotype.capacity(); i++)
		genotype.push_back(i % (Ngene::numbers / 2));
	random_shuffle(genotype.begin(), genotype.end());
}

const char *species()
{
	return Ngene::name.c_str();
}

const char *str(const vector<boost::any> &genotype)
{
	ostringstream phenotype;
	for (vector<boost::any>::const_iterator i = genotype.begin(); i != genotype.end(); i++)
		phenotype << boost::any_cast<unsigned int>(*i) << " ";
	Ngene::output = phenotype.str();
	return Ngene::output.c_str();
}

