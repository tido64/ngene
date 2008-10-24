#if WIN32
	#define WIN32_LEAN_AND_MEAN
	#include <windows.h>
	#undef max
	#define dlhandle HMODULE
	#define dlsym GetProcAddress
	#define dlclose FreeLibrary
#else
	#include <dlfcn.h>
	typedef void * dlhandle;	//< Custom type definition to make dynamic library loading cross-platform
#endif

/// Handles all module loading and acts as an interface for the rest of the
/// system.

#include "Config.h"
#include "ModuleType.h"
#include "Plugins.h"

class PluginManager
{
public:
	int offspring_rate;					///< The number of offspring produced each generation
	std::vector<const char *> modules;	///< Stores the names of the loaded modules

	Fitness assess_fitness;				///< Assesses an individual
	GenerateGenotype seed;				///< Randomly generates an individual
	GenotypeToStr genotype_to_str;		///< Returns a string representing the individual
	Mating mate;						///< Crosses over two individuals' genes
	Mutator mutate;						///< Mutates a genotype
	Phenotype phenotype;				///< Returns the phenotype of given genotype
	Selector select;					///< Selects an individual out of a population

	/// Loads the modules specificed by the config file and readies an
	/// interface for the modules accessible for the rest of the system.
	/// \param config  The configuration to abide by
	PluginManager(const Config *config);
	~PluginManager();

private:
	/// Stores the handlers for the dynamically loaded libraries. Used for
	/// cleaning up the memory allocated after termination.
	std::vector<dlhandle> dlhandles;

	/// Handles the actual loading of a module.
	/// \param module_type	The type of the module to load
	/// \param filename		The filename of the module
	/// \param parameters	The parameters to send to the module
	void load_module(const Module::Type module_type, const std::string &filename, const std::string &parameters);
};
