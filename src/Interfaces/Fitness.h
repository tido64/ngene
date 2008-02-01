#ifndef FITNESS_INTERFACE

#ifdef WIN32
	#define FITNESS_INTERFACE __declspec(dllexport)	// export DLL information
#else
	#define FITNESS_INTERFACE
#endif

#include "../Plugins.h"

namespace Ngene
{
	/// A pointer to \ref Genotype.h::phenotype. Must be set by PluginManager.
	Phenotype phenotype;
}

extern "C"
{
	/// Assess an individual. The genotype is extracted through
	/// individual.genotype, and the fitness is given to individual.fitness.
	/// \param[in,out] individual The individual to assess
	void FITNESS_INTERFACE assess(Specimen &individual);

	/// Sends a pointer to function Genotype.h::phenotype, needed by
	/// Fitness.h::assess.
	void FITNESS_INTERFACE assign_phenotype_function(Phenotype *fn)
	{
		Ngene::phenotype = *fn;
	}

	/// Sets up the module and makes sure it is ready for use. Every module is
	/// initiated this way.
	/// \param parameters The parameters needed to correctly set up the module
	void FITNESS_INTERFACE initiate(const std::string &parameters);

	/// Returns the name of this module.
	const char FITNESS_INTERFACE *name();
}

#endif
