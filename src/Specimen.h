/// An individual carrying a specific genotype in a population.

#ifndef SPECIMEN_INTERFACE
#define SPECIMEN_INTERFACE

#include <vector>
#include <boost/any.hpp>

typedef std::vector<boost::any> Genotype;	///< Defines the genotype type

class Specimen
{
public:
	mutable unsigned int age;				///< The age of this individual
	double fitness;							///< The fitness of this individual compared to an ideal phenotype
	Genotype genotype;						///< The genotype of this individual

	/// A custom < for use with std::multiset. This sorts the population after
	/// their fitness in a descending order.
	bool operator< (const Specimen &individual) const
	{
		return this->fitness > individual.fitness;
	}
};

typedef std::vector<Specimen> Population;

#endif
