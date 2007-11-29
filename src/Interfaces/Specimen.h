#ifndef SPECIMEN_INTERFACE
#define SPECIMEN_INTERFACE

#include <vector>
#include <boost/any.hpp>

class Specimen
{
public:
	mutable int age;
	double fitness;
	std::vector<boost::any> genotype;

	bool operator< (const Specimen &individual) const
	{
		return this->fitness > individual.fitness;
	}
};

#endif
