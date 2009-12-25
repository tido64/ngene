#ifdef WIN32
#	define MUTATOR_INTERFACE __declspec(dllexport)	// export DLL information
#else
#	define MUTATOR_INTERFACE
#endif

#include <Random.h>
#include <Specimen.h>

namespace ngene
{
	Random *random;
}

extern "C"
{
	/// Retrieves convenient and essential functions for this module
	void MUTATOR_INTERFACE assign_functions(Random *fn_random)
	{
		ngene::random = fn_random;
	}

	/// Sets up the module and makes sure it is ready for use. Every module is
	/// initiated this way.
	/// \param parameters  The parameters needed to correctly set up the module
	void MUTATOR_INTERFACE initiate(const char *parameters);

	/// Mutates given genotype.
	/// \param[in,out] genotype  The genotype to mutate
	void MUTATOR_INTERFACE mutate(Genotype &genotype);

	/// Returns the name of this module.
	const char MUTATOR_INTERFACE *name();
}
