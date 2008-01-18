#ifdef WIN32
	#define MUTATION_INTERFACE __declspec(dllexport)	// export DLL information
#else
	#define MUTATION_INTERFACE
#endif

#include <string>
#include "Specimen.h"

extern "C"
{
	void MUTATION_INTERFACE initiate(const std::string &parameters);

	/// Mutates a genotype.
	void MUTATION_INTERFACE mutate(Genotype &genotype);

	const char MUTATION_INTERFACE *name();
}
