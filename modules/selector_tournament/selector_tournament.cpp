#include "../../src/Interfaces/Selector.h"
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <sstream>

namespace tournament
{
	std::string name;
	unsigned int k;
	double p;
	double random()
	{
		return (double)rand() / ((double)RAND_MAX + 1.0);
	}
}


using std::multiset;
using std::set;
using std::string;

void initiate(const string &parameters)
{
	std::istringstream parse (parameters);
	parse >> tournament::k >> tournament::p;
	std::ostringstream in_name;
	in_name << "Tournament (k=" << tournament::k << ", p=" << tournament::p << ")";
	tournament::name = in_name.str();
	srand((unsigned int)time(NULL));
}

void gene_select(Population::iterator &champ, Population &candidates, int generation)
{
	set<int> selection;
	while (selection.size() < tournament::k)
		selection.insert((int)(candidates.size() * tournament::random()));

	int counter = 0;
	champ = candidates.begin();
	for (set<int>::iterator i = selection.begin(); i != selection.end(); i++)
	{
		if (tournament::random() <= tournament::p * pow(1.0 - tournament::p, counter++))
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
