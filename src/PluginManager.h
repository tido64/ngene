#include <cstdio>
#include <set>
#include <string>
#include <vector>
#include <boost/any.hpp>

#ifdef WIN32
	#define WIN32_LEAN_AND_MEAN
	#include <windows.h>
	#define dlsym GetProcAddress
#else
	#include <dlfcn.h>
#endif

#include "Config.h"
#include "ModuleType.h"
#include "Interfaces/Specimen.h"

using std::multiset;
using std::string;
using std::vector;
using boost::any;

class PluginManager
{
	// common functions
	typedef void (*initiate)(const string &);
	typedef const char *(*module_name)();
	typedef const int (*offspring_produced)();

	// module specific functions
	typedef void (*Fitness)(Specimen &);
	typedef void (*Gene)(vector<any> &);
	typedef const char *(*GenotypeToStr)(const vector<any> &);
	typedef void (*Mating)(vector<Specimen> &, const Specimen &, const Specimen &);
	typedef void (*Mutator)(vector<any> &);
	typedef void (*Selector)(multiset<Specimen>::iterator &, multiset<Specimen> &, int);

	template <class T>
	void load_module(const ModuleType module_type, string &path, const string &parameters, const char *import, T &function)
	{
		path = "./modules/" + path;
		#ifdef WIN32
			HMODULE module (LoadLibraryA(path.c_str()));
		#else
			void *module = dlopen(path.c_str(), RTLD_LAZY);
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
		}
	}

public:
	int offspring_rate;
	vector<const char *> modules;

	Fitness fitness_assess;
	Gene seed;
	GenotypeToStr genotype_to_str;
	Mating mate;
	Mutator mutate;
	Selector select;

	PluginManager(Config &config);
	~PluginManager();
};

