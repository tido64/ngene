#include <set>

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

#include "Interfaces/Specimen.h"
#include "Config.h"
#include "ModuleType.h"

class PluginManager
{
	// common functions
	typedef void (*initiate)(const std::string &);
	typedef const char *(*module_name)();
	typedef const int (*offspring_produced)();

	// module specific functions
	typedef void (*Fitness)(Specimen &);
	typedef void (*Gene)(std::vector<boost::any> &);
	typedef const char *(*GenotypeToStr)(const std::vector<boost::any> &);
	typedef void (*Mating)(std::vector<Specimen> &, const Specimen &, const Specimen &);
	typedef void (*Mutator)(std::vector<boost::any> &);
	typedef void (*Selector)(std::multiset<Specimen>::iterator &, std::multiset<Specimen> &, int);

	// dynamic library handlers
	std::vector<dlhandle> dlhandles;

	template <class T>
	void load_module(const ModuleType module_type, std::string path, const std::string &parameters, const char *import, T &function)
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
				case gene_module:
					this->genotype_to_str = (GenotypeToStr)dlsym(module, "str");
					this->modules[module_type] = ((module_name)dlsym(module, "species"))();
					break;
				case mating_module:
					this->offspring_rate = ((offspring_produced)dlsym(module, "offspring"))();
				default:
					this->modules[module_type] = ((module_name)dlsym(module, "name"))();
					break;
			}
			dlhandles.push_back(module);
		}
	}

public:
	int offspring_rate;
	std::vector<const char *> modules;

	Fitness fitness_assess;
	Gene seed;
	GenotypeToStr genotype_to_str;
	Mating mate;
	Mutator mutate;
	Selector select;

	PluginManager(const Config &config);
	~PluginManager();
};
