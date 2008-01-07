#ifndef FITNESS_INTERFACE

#ifdef WIN32
	#define FITNESS_INTERFACE __declspec(dllexport)	// export DLL information
#else
	#define FITNESS_INTERFACE
#endif

#include "Specimen.h"

extern "C"
{
	void FITNESS_INTERFACE assess(Specimen &individual);
	void FITNESS_INTERFACE initiate(const std::string &parameters);
	const char FITNESS_INTERFACE *name();
}

#endif
