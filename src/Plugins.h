#ifndef PLUGINS_H_
#define PLUGINS_H_

#include "Specimen.h"

/// A pointer to \ref Fitness.h::assess.
typedef void (*Fitness)(Specimen &);

/// A pointer to \ref Genotype.h::phenotype.
typedef void (*Phenotype)(Any &phenotype, const Genotype &);

/// A pointer to \ref Genotype.h::seed.
typedef void (*Seed)(Genotype &);

/// A pointer to \ref Genotype.h::str.
typedef const char *(*GenotypeToStr)(const Genotype &);

/// A pointer to \ref Mating.h::mate.
typedef void (*Mating)(std::vector<Specimen> &, const Specimen &, const Specimen &);

/// A pointer to \ref Mating.h::offspring.
typedef unsigned int (*offspring_produced)();

/// A pointer to \ref Mutator.h::mutate.
typedef void (*Mutator)(Genotype &);

/// A pointer to \ref Selector.h::gene_select.
typedef void (*Selector)(Population::iterator &, Population &, int);

#endif
