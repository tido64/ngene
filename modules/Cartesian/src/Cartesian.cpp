#include "Cartesian.h"

using std::map;
using std::vector;

double Cartesian::diffuse(const double lvl, const vector<Message> &in)
{
	double sum (0);
	for (vector<Message>::const_iterator i = in.begin(); i != in.end(); i++)
		sum += i->chemicals[0];
	return (lvl / 2) + (sum / 16);
}

void Cartesian::execute(Cell &c)
{
	unsigned int fn (NUMBER_OF_FUNCTIONS >> 1);
}

void Cartesian::initialize(Organism *o)
{
	// Translate genotype into appropriate data structure
	this->system.clear();
	for (vector<boost::any>::const_iterator i = o->genotype.begin(); i != o->genotype.end(); i++)
		this->system.push_back(boost::any_cast<unsigned int>(i));
	// first cell
}
