#ifdef WIN32
	#define GENE_FACTORY_INTERFACE __declspec(dllexport)	// export DLL information
#else
	#define GENE_FACTORY_INTERFACE
#endif

#include <string>
#include <vector>
#include <boost/any.hpp>
#include "Specimen.h"

extern "C"
{
	void GENE_FACTORY_INTERFACE initiate(const std::string &parameters);
	void GENE_FACTORY_INTERFACE seed(std::vector<boost::any> &genotype);
	const char GENE_FACTORY_INTERFACE *species();
	const char GENE_FACTORY_INTERFACE *str(const std::vector<boost::any> &genotype);
}
