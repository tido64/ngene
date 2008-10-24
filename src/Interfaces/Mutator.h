#ifdef WIN32
#	define MUTATION_INTERFACE __declspec(dllexport)	// export DLL information
#else
#	define MUTATION_INTERFACE
#endif

#include <string>
#include "../Specimen.h"

extern "C"
{
	/// Sets up the module and makes sure it is ready for use. Every module is
	/// initiated this way.
	/// \param parameters  The parameters needed to correctly set up the module
	void MUTATION_INTERFACE initiate(const char *parameters);

	/// Mutates given genotype.
	/// \param[in,out] genotype  The genotype to mutate
	void MUTATION_INTERFACE mutate(Genotype &genotype);

	/// Returns the name of this module.
	const char MUTATION_INTERFACE *name();
}
