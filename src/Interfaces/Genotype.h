#ifdef WIN32
	#define GENOTYPE_INTERFACE __declspec(dllexport)	// export DLL information
#else
	#define GENOTYPE_INTERFACE
#endif

#include <string>
#include "../Specimen.h"

extern "C"
{
	/// Sets up the module and makes sure it is ready for use. Every module is
	/// initiated this way.
	/// \param parameters The parameters needed to correctly set up the module
	void GENOTYPE_INTERFACE initiate(const char *parameters);

	/// Returns the phenotype of given genotype.
	/// \param[out]	phenotype	The phenotype returned
	/// \param		genotype	The genotype of the wanted phenotype
	void GENOTYPE_INTERFACE *phenotype(const Genotype &genotype);

	/// Generates a random genotype.
	/// \param[out] genotype The newly generated genotype
	void GENOTYPE_INTERFACE seed(Genotype &genotype);

	/// Returns the name of the species.
	const char GENOTYPE_INTERFACE *species();

	/// Returns the string representation of the genotype. Typically used for
	/// saving to file.
	const char GENOTYPE_INTERFACE *str(const Genotype &genotype);
}
