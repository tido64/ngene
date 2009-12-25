#include <Fitness.h>

#include <list>
#include <string>

using std::list;
using std::string;

void assess(Specimen &individual)
{
	list<int> order;
	for (int i = 0; i < (int)individual.genotype.size(); i++)
		order.push_back(i);
	list<int>::iterator iter;
	int pt;
	individual.fitness = individual.genotype.size();
	for (int i = 0; i < (int)individual.genotype.size(); i++)
	{
		iter = order.begin();
		pt = boost::any_cast<unsigned int>(individual.genotype[i]) % order.size();
		for (int j = 0; j < pt; j++)
			iter++;
		if (*iter != i)
			individual.fitness--;
		order.erase(iter);
	}
	individual.fitness /= (double)individual.genotype.size();
}

void initiate(const char *parameters) { }

const char *name()
{
	return "Unsorted";
}
