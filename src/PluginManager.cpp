#include "PluginManager.h"

PluginManager::PluginManager(Config &config)
{
	modules = vector<const char *> (number_of_modules);

	this->load_module<Gene>(gene_module,
		config.module_path[gene_module],
		config.parameters[gene_module],
		"seed",
		this->seed);
	this->load_module<Fitness>(fitness_module,
		config.module_path[fitness_module],
		config.parameters[fitness_module],
		"assess",
		this->fitness_assess);
	this->load_module<Mating>(mating_module,
		config.module_path[mating_module],
		config.parameters[mating_module],
		"mate",
		this->mate);
	this->load_module<Mutator>(mutator_module,
		config.module_path[mutator_module],
		config.parameters[mutator_module],
		"mutate",
		this->mutate);
	this->load_module<Selector>(selector_module,
		config.module_path[selector_module],
		config.parameters[selector_module],
		"gene_select",
		this->select);
}

PluginManager::~PluginManager()
{
	this->modules.clear();
	for (vector<dlhandle>::iterator i = this->dlhandles.begin(); i != this->dlhandles.end(); i++)
		dlclose(*i);
	this->dlhandles.clear();
}
