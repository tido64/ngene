#ifdef WIN32
	#define SELECTION_INTERFACE __declspec(dllexport)	// export DLL information
#else
	#define SELECTION_INTERFACE
#endif
#include <set>
#include <string>
#include <vector>
#include "Specimen.h"

extern "C"
{
	void SELECTION_INTERFACE initiate(const std::string &parameters);
	void SELECTION_INTERFACE gene_select(std::multiset<Specimen>::iterator &champ, std::multiset<Specimen> &candidates, int generation);
	const char SELECTION_INTERFACE *name();
}

