#ifdef WIN32
#	define MATING_INTERFACE __declspec(dllexport)	// export DLL information
#else
#	define MATING_INTERFACE
#endif

#include <Random.h>
#include <Specimen.h>

namespace ngene
{
	Random *random;
}

extern "C"
{
	/// Assigns convenient and essential functions for this module
	void MATING_INTERFACE assign_functions(Random *fn_random)
	{
		ngene::random = fn_random;
	}

	/// Sets up the module and makes sure it is ready for use. Every module is
	/// initiated this way.
	/// \param parameters  The parameters needed to correctly set up the module
	void MATING_INTERFACE initiate(const char *parameters);

	/// Crosses over two individuals and produces offspring.
	/// \param[out] children  The child(ren) produced
	/// \param parentA        The first individual of the cross over process
	/// \param parentB        The other individual of the cross over process
	void MATING_INTERFACE mate(std::vector<Specimen> &children, const Specimen &parentA, const Specimen &parentB);

	/// Returns the name of this module.
	const char MATING_INTERFACE *name();

	/// Returns the number of offspring this module produces.
	unsigned int MATING_INTERFACE offspring();
}
