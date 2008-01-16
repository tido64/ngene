#ifdef WIN32
	#define MATING_INTERFACE __declspec(dllexport)	// export DLL information
#else
	#define MATING_INTERFACE
#endif

#include <map>
#include <string>
#include "Specimen.h"

extern "C"
{
	void MATING_INTERFACE initiate(const std::string &parameters);

	/// Crosses over two individuals and produces offspring.
	/// \param[out] children The child(ren) produced
	/// \param parentA The first individual of the cross over process
	/// \param parentB The other individual of the cross over process
	void MATING_INTERFACE mate(std::vector<Specimen> &children, const Specimen &parentA, const Specimen &parentB);

	const char MATING_INTERFACE *name();
	const int MATING_INTERFACE offspring();
}
