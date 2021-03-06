/// An individual carrying a specific genotype in a population.

#ifndef SPECIMEN_H_
#define SPECIMEN_H_

#include <algorithm>
#include <vector>

#include "Any.h"

#define best_specimen std::min_element   ///< For finding the best specimen in a population
#define worst_specimen std::max_element  ///< For finding the worst specimen in a population

class Specimen;
typedef std::vector<Any> Genotype;         ///< Defines the genotype type
typedef std::vector<Specimen> Population;  ///< Defines the population type

class Specimen
{
public:
#ifdef ENABLE_LIFESPAN
	mutable unsigned int age;  ///< The age of this individual
#endif
	double fitness;     ///< The fitness of this individual compared to an ideal phenotype
	Genotype genotype;  ///< The genotype of this individual

	/// Sort the population after their fitness in descending order.
	bool operator <(const Specimen &individual) const
	{
		return this->fitness > individual.fitness;
	}
};

#endif
