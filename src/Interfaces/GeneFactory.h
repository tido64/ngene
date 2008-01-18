#ifdef WIN32
	#define GENE_FACTORY_INTERFACE __declspec(dllexport)	// export DLL information
#else
	#define GENE_FACTORY_INTERFACE
#endif

#include <string>
#include "Specimen.h"

extern "C"
{
	void GENE_FACTORY_INTERFACE initiate(const std::string &parameters);
	void GENE_FACTORY_INTERFACE seed(Genotype &genotype);
	const char GENE_FACTORY_INTERFACE *species();
	const char GENE_FACTORY_INTERFACE *str(Genotype &genotype);
}
