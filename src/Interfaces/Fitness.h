#ifndef FITNESS_INTERFACE

#ifdef WIN32
	#define FITNESS_INTERFACE __declspec(dllexport)	// export DLL information
#else
	#define FITNESS_INTERFACE
#endif

#include "Specimen.h"

extern "C"
{
	/// Assess an individual. The genotype is extracted through
	/// individual.genotype, and the fitness is given to individual.fitness.
	/// \param[in,out] individual The individual to assess
	void FITNESS_INTERFACE assess(Specimen &individual);
	void FITNESS_INTERFACE initiate(const std::string &parameters);
	const char FITNESS_INTERFACE *name();
}

#endif
