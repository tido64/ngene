#include <cmath>
#include <sstream>
#include "../../src/Interfaces/Selector.h"
#include "../../src/Random.h"


namespace tournament
{
	std::string name;
	unsigned int k;
	double p;
}


using std::set;
using std::string;
using std::stringstream;

void initiate(const char *parameters)
{
	stringstream s (parameters);
	s >> tournament::k >> tournament::p;
	s.clear();
	s.str("");
	s << "Tournament (k=" << tournament::k << ", p=" << tournament::p << ")";
	tournament::name = s.str();
}

void gene_select(Population::iterator &champ, Population &candidates, int generation)
{
	set<int> selection;
	while (selection.size() < tournament::k)
		selection.insert(Random::Instance().next_int(candidates.size()));

	int counter = 0;
	champ = candidates.begin();
	for (set<int>::iterator i = selection.begin(); i != selection.end(); i++)
	{
		if (Random::Instance().next() <= tournament::p * pow(1.0 - tournament::p, counter++))
		{
			for (int j = 0; j < *i; j++)
				champ++;
			return;
		}
	}
}

const char *name()
{
	return tournament::name.c_str();
}
