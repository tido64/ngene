#include "PluginManager.h"

PluginManager::PluginManager(SettingsManager &settings_manager)
{
	modules = vector<const char *> (number_of_modules);

	this->load_module<Gene>(gene_module,
		settings_manager.config.module_path[gene_module],
		settings_manager.config.parameters[gene_module],
		"seed",
		this->seed);
	this->load_module<Fitness>(fitness_module,
		settings_manager.config.module_path[fitness_module],
		settings_manager.config.parameters[fitness_module],
		"assess",
		this->fitness_assess);
	this->load_module<Mating>(mating_module,
		settings_manager.config.module_path[mating_module],
		settings_manager.config.parameters[mating_module],
		"mate",
		this->mate);
	this->load_module<Mutator>(mutator_module,
		settings_manager.config.module_path[mutator_module],
		settings_manager.config.parameters[mutator_module],
		"mutate",
		this->mutate);
	this->load_module<Selector>(selector_module,
		settings_manager.config.module_path[selector_module],
		settings_manager.config.parameters[selector_module],
		"gene_select",
		this->select);
}

