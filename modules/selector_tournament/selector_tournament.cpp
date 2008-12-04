#include <cmath>
#include <set>
#include <sstream>
#include <Selector.h>

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
		selection.insert(ngene::random->next_int(candidates.size()));

	int counter = 0;
	for (set<int>::iterator i = selection.begin(); i != selection.end(); i++)
	{
		if (ngene::random->next() <= tournament::p * pow(1.0 - tournament::p, counter++))
		{
			champ = candidates.begin() + *i;
			return;
		}
	}
	champ = best_specimen(candidates.begin(), candidates.end());
}

const char *name()
{
	return tournament::name.c_str();
}
