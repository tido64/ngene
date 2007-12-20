/// An individual in a population

#ifndef SPECIMEN_INTERFACE
#define SPECIMEN_INTERFACE

#include <vector>
#include <boost/any.hpp>

class Specimen
{
public:
	mutable unsigned int age;			///< The age of this individual
	double fitness;						///< The fitness of this individual
	std::vector<boost::any> genotype;	///< The genotype of this individual

	/// A custom < for use with std::multiset. This sorts the population after
	/// their fitness in a descending order.
	bool operator< (const Specimen &individual) const
	{
		return this->fitness > individual.fitness;
	}
};

#endif
