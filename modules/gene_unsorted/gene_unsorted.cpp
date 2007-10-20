#include "gene_unsorted.h"

using std::vector;
using boost::any;
using boost::any_cast;

void initiate(const std::string &parameters)
{
	Unsorted::numbers = atoi(parameters.c_str());
}

void seed(vector<any> &genotype)
{
	genotype.reserve(Unsorted::numbers);
	for (int i = 0; i < (int)genotype.capacity(); i++)
		genotype.push_back(i % (Unsorted::numbers / 2));
	random_shuffle(genotype.begin(), genotype.end());
}

const char *str(const vector<any> &genotype)
{
	std::ostringstream phenotype;
	for (vector<any>::const_iterator i = genotype.begin(); i != genotype.end(); i++)
		phenotype << any_cast<int>(*i) << " ";
	Unsorted::output = phenotype.str();
	return Unsorted::output.c_str();
}

