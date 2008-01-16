#include "PluginManager.h"

using std::vector;

PluginManager::PluginManager(const Config &config)
{
	this->modules = vector<const char *> (Module::number_of_types);

	this->load_module<GenerateGenotype>(Module::gene,
		config.module_path[Module::gene],
		config.parameters[Module::gene],
		"seed",
		this->seed);
	this->load_module<Fitness>(Module::fitness,
		config.module_path[Module::fitness],
		config.parameters[Module::fitness],
		"assess",
		this->fitness_assess);
	this->load_module<Mating>(Module::mating,
		config.module_path[Module::mating],
		config.parameters[Module::mating],
		"mate",
		this->mate);
	this->load_module<Mutator>(Module::mutator,
		config.module_path[Module::mutator],
		config.parameters[Module::mutator],
		"mutate",
		this->mutate);
	this->load_module<Selector>(Module::selector,
		config.module_path[Module::selector],
		config.parameters[Module::selector],
		"gene_select",
		this->select);
}

PluginManager::~PluginManager()
{
	for (vector<dlhandle>::iterator i = this->dlhandles.begin(); i != this->dlhandles.end(); i++)
		dlclose(*i);
}
