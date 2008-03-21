/// An individual carrying a specific genotype in a population.

#ifndef SPECIMEN_INTERFACE
#define SPECIMEN_INTERFACE

#include <algorithm>
#include <vector>
#include <boost/any.hpp>

#define best_specimen std::min_element		///< For finding the best specimen in a population
#define worst_specimen std::max_element		///< For finding the worst specimen in a population

class Specimen;
typedef std::vector<Specimen> Population;	///< Defines the population type
typedef std::vector<boost::any> Genotype;	///< Defines the genotype type

class Specimen
{
public:
	mutable unsigned int age;				///< The age of this individual
	double fitness;							///< The fitness of this individual compared to an ideal phenotype
	Genotype genotype;						///< The genotype of this individual

	/// Sort the population after their fitness in descending order.
	bool operator< (const Specimen &individual) const
	{
		return this->fitness > individual.fitness;
	}
};

#endif
