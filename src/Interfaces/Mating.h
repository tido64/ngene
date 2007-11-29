#ifdef WIN32
	#define MATING_INTERFACE __declspec(dllexport)	// export DLL information
#else
	#define MATING_INTERFACE
#endif
#include <map>
#include <string>
#include <vector>
#include "Specimen.h"

extern "C"
{
	void MATING_INTERFACE initiate(const std::string &parameters);
	void MATING_INTERFACE mate(std::vector<Specimen> &children, const Specimen &parentA, const Specimen &parentB);
	const char MATING_INTERFACE *name();
	const int MATING_INTERFACE offspring();
}
