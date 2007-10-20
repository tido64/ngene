#ifdef WIN32
	#define MUTATION_INTERFACE __declspec(dllexport)	// export DLL information
#else
	#define MUTATION_INTERFACE
#endif
#include <string>
#include <vector>
#include <boost/any.hpp>

extern "C"
{
	void MUTATION_INTERFACE initiate(const std::string &parameters);
	void MUTATION_INTERFACE mutate(std::vector<boost::any> &genotype);
	const char MUTATION_INTERFACE *name();
}

