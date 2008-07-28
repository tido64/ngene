#ifdef WIN32
#	define SELECTION_INTERFACE __declspec(dllexport)	// export DLL information
#else
#	define SELECTION_INTERFACE
#endif

#include <string>
#include "../Specimen.h"

extern "C"
{
	/// Sets up the module and makes sure it is ready for use. Every module is
	/// initiated this way.
	/// \param parameters The parameters needed to correctly set up the module
	void SELECTION_INTERFACE initiate(const char *parameters);

	/// Randomly selects an individual from a population.
	/// \param[out] champ The selected individual
	/// \param candidates The population to perform selection over
	/// \param generation The current generation
	void SELECTION_INTERFACE gene_select(Population::iterator &champ, Population &candidates, int generation);

	/// Returns the name of this module.
	const char SELECTION_INTERFACE *name();
}
