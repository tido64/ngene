#include "PluginManager.h"

using std::string;
using std::vector;

PluginManager::PluginManager(const Config *config) :
	random(Random::Instance()),
	modules(Module::number_of_types, 0)
{
	this->dlhandles.reserve(Module::number_of_types);
	this->load_module(Module::gene, config->module_path[Module::gene], config->parameters[Module::gene]);
	this->load_module(Module::fitness, config->module_path[Module::fitness], config->parameters[Module::fitness]);
	this->load_module(Module::mating, config->module_path[Module::mating], config->parameters[Module::mating]);
	this->load_module(Module::mutator, config->module_path[Module::mutator], config->parameters[Module::mutator]);
	this->load_module(Module::selector, config->module_path[Module::selector], config->parameters[Module::selector]);
}

PluginManager::~PluginManager()
{
	for (vector<dlhandle>::iterator i = this->dlhandles.begin(); i != this->dlhandles.end(); i++)
		dlclose(*i);
}

void PluginManager::load_module(const Module::Type module_type, const string &filename, const string &parameters)
{
	string dl = "./modules/";
	dl.append(filename);
	#ifdef WIN32
		dlhandle module (LoadLibraryA(dl.c_str()));
	#else
		dlhandle module = dlopen(dl.c_str(), RTLD_LAZY);
	#endif
	if (module == 0)
	{
		printf("==> Failed to load %s\n", filename.c_str());
		exit(-1);
	}
	else
	{
		dl = "name";
		((void (*)(const char *))dlsym(module, "initiate"))(parameters.c_str());
		if (module_type == Module::fitness)
		{
			((void (*)(Phenotype *))dlsym(module, "assign_functions"))(&this->phenotype);
			this->assess_fitness = (Fitness)dlsym(module, "assess");
		}
		else
		{
			((void (*)(Random *))dlsym(module, "assign_functions"))(this->random);
			switch (module_type)
			{
				case Module::gene:
					this->phenotype = (Phenotype)dlsym(module, "phenotype");
					this->seed = (Seed)dlsym(module, "seed");
					this->gtoa = (GenotypeToStr)dlsym(module, "str");
					dl = "species";
					break;
				case Module::mating:
					this->mate = (Mating)dlsym(module, "mate");
					this->offspring_rate = ((offspring_produced)dlsym(module, "offspring"))();
					break;
				case Module::mutator:
					this->mutate = (Mutator)dlsym(module, "mutate");
					break;
				case Module::selector:
					this->select = (Selector)dlsym(module, "gene_select");
					break;
				default:
					break;
			}
		}
		this->modules[module_type] = ((const char *(*)())dlsym(module, dl.c_str()))();
		dlhandles.push_back(module);
	}
}
