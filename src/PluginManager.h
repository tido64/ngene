#ifdef WIN32
	#define WIN32_LEAN_AND_MEAN
	#include <windows.h>
	#define dlhandle HMODULE
	#define dlsym GetProcAddress
	#define dlclose FreeLibrary
#else
	#include <dlfcn.h>
	#define dlhandle void *
#endif

/// Handles all module loading and acts as an interface for the rest of the
/// system.

#include <set>

#include "Interfaces/Specimen.h"
#include "Config.h"
#include "ModuleType.h"

class PluginManager
{
	/// An access point for all modules. Sets up a module with given
	/// parameters. A common method required in all modules.
	typedef void (*initiate)(const std::string &);

	/// Returns the name of a module. A common method required in all modules.
	typedef const char *(*module_name)();

	/// Returns the number of offspring produced for each generation. Loaded
	/// from a mating module.
	typedef const int (*offspring_produced)();

	/// A pointer to a function that assesses the fitness of an individual
	/// \param[in,out] Specimen The individual to be assessed
	typedef void (*Fitness)(Specimen &);

	/// A pointer to a function that generates random genotypes
	/// \param[out] std::vector<boost::any> An empty gene to inject a genotype into
	typedef void (*GenerateGenotype)(Genotype &);

	/// A pointer to a function that makes a string out of a genotype
	/// \param std::vector<boost::any> The genotype
	typedef const char *(*GenotypeToStr)(const Genotype &);

	/// A pointer to a function that crosses over two individuals
	/// \param[out] std::vector<Specimen> The container that carries the offspring produced
	/// \param Specimen An individual to cross over with
	/// \param Speciman The other individual
	typedef void (*Mating)(std::vector<Specimen> &, const Specimen &, const Specimen &);

	/// A pointer to a function that mutates a genotype
	/// \param[in,out] std::vector<boost::any> The genotype to mutate
	typedef void (*Mutator)(Genotype &);

	/// A pointer to a function that selects an individual out of a population
	/// \param[out] std::multiset<Specimen>::iterator An std::multiset::iterator to the selected individual
	/// \param std::multiset<Specimen> The population to perform a selection over
	/// \param int The number of generations elapsed
	typedef void (*Selector)(std::multiset<Specimen>::iterator &, std::multiset<Specimen> &, int);

	/// Stores the handlers for the dynamically loaded libraries. Used for
	/// cleaning up the memory allocated after termination.
	std::vector<dlhandle> dlhandles;

	/// Handles the actual loading of a module.
	/// \param module_type The type of the module to load
	/// \param path The path to the module to load
	/// \param parameters The parameters to use with 
	/// \param import The function to import from the module
	/// \param function An empty pointer to store the function pointer
	template <class T>
	void load_module(const Module::Type module_type, std::string path, const std::string &parameters, const char *import, T &function)
	{
		path = "./modules/" + path;
		#ifdef WIN32
			dlhandle module (LoadLibraryA(path.c_str()));
		#else
			dlhandle module = dlopen(path.c_str(), RTLD_LAZY);
		#endif
		if (module != NULL)
		{
			((initiate)dlsym(module, "initiate"))(parameters);
			function = (T)dlsym(module, import);
			switch (module_type)
			{
				case Module::gene:
					this->genotype_to_str = (GenotypeToStr)dlsym(module, "str");
					this->modules[module_type] = ((module_name)dlsym(module, "species"))();
					break;
				case Module::mating:
					this->offspring_rate = ((offspring_produced)dlsym(module, "offspring"))();
				default:
					this->modules[module_type] = ((module_name)dlsym(module, "name"))();
					break;
			}
			dlhandles.push_back(module);
		}
	}

public:
	int offspring_rate;					///< The number of offspring produced each generation
	std::vector<const char *> modules;	///< Stores the names of the modules loaded

	Fitness fitness_assess;				///< Assesses an individual
	GenerateGenotype seed;				///< Randomly generates an individual
	GenotypeToStr genotype_to_str;		///< Returns a string representing the individual
	Mating mate;						///< Crosses over two individuals' genes
	Mutator mutate;						///< Mutates a genotype
	Selector select;					///< Selects an individual out of a population

	/// Loads the modules specificed by the config file and readies an
	/// interface for the modules accessible for the rest of the system.
	/// \param config The configuration to abide by
	PluginManager(const Config &config);
	~PluginManager();
};
