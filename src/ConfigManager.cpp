#include "ConfigManager.h"
#include "Config.h"
#include "ModuleType.h"

using std::map;
using std::string;

const void *ConfigManager::parse()
{
	const string
		capacity			= "capacity",
		elitism				= "elitism",
		empty,
		fitness_parameters	= "fitness:parameters",
		fitness_path		= "fitness:path",
		generations			= "generations",
		genotype_parameters	= "genotype:parameters",
		genotype_path		= "genotype:path",
		lifespan			= "lifespan",
		mating_parameters	= "mating:parameters",
		mating_path			= "mating:path",
		mating_rate			= "mating rate",
		mutation_rate		= "mutation rate",
		mutator_parameters	= "mutator:parameters",
		mutator_path		= "mutator:path",
		offspring_rate		= "offspring rate",
		prodigies			= "prodigies",
		selector_parameters	= "selector:parameters",
		selector_path		= "selector:path";

	Config *cfg (new Config());

	if (this->conf.find(capacity) == this->conf.end())
		cfg->capacity = 100;
	else
		cfg->capacity = atoi(this->conf[capacity].c_str());

	if (this->conf.find(generations) == this->conf.end())
		cfg->doomsday = 50;
	else
		cfg->doomsday = atoi(this->conf[generations].c_str());

	if (this->conf.find(elitism) == this->conf.end())
		cfg->elitism = false;
	else
		cfg->elitism = (atoi(this->conf[elitism].c_str()) == 1) ? true : false;

	if (this->conf.find(lifespan) == this->conf.end())
		cfg->lifespan = 1;
	else
		cfg->lifespan = atoi(this->conf[lifespan].c_str());

	if (this->conf.find(mating_rate) == this->conf.end())
		cfg->mating_rate = 0.9;
	else
		cfg->mating_rate = atof(this->conf[mating_rate].c_str());

	if (this->conf.find(mutation_rate) == this->conf.end())
		cfg->mutation_rate = 0.2;
	else
		cfg->mutation_rate = atof(this->conf[mutation_rate].c_str());

	if (this->conf.find(offspring_rate) == this->conf.end())
		cfg->offspring_rate = static_cast<unsigned int>(cfg->capacity + cfg->capacity * 0.1);
	else
		cfg->offspring_rate = atoi(this->conf[offspring_rate].c_str());

	if (this->conf.find(prodigies) == this->conf.end())
		cfg->prodigies = static_cast<unsigned int>(cfg->capacity * 0.3);
	else
		cfg->prodigies = atoi(this->conf[prodigies].c_str());

	cfg->module_path.assign(Module::number_of_types, empty);
	cfg->parameters.assign(Module::number_of_types, empty);

	if (this->conf.find(genotype_path) == this->conf.end())
	{
		printf("==> No path was found for the genotype module\n");
		exit(-1);
	}
	else
	{
		cfg->module_path[Module::gene] = this->conf[genotype_path];
		cfg->parameters[Module::gene] = this->conf[genotype_parameters];
	}

	if (this->conf.find(fitness_path) == this->conf.end())
	{
		printf("==> No path was found for the fitness module\n");
		exit(-1);
	}
	else
	{
		cfg->module_path[Module::fitness] = this->conf[fitness_path];
		cfg->parameters[Module::fitness] = this->conf[fitness_parameters];
	}

	if (this->conf.find(mating_path) == this->conf.end())
	{
		printf("==> No path was found for the mating module\n");
		exit(-1);
	}
	else
	{
		cfg->module_path[Module::mating] = this->conf[mating_path];
		cfg->parameters[Module::mating] = this->conf[mating_parameters];
	}

	if (this->conf.find(mutator_path) == this->conf.end())
	{
		printf("==> No path was found for the mutator module\n");
		exit(-1);
	}
	else
	{
		cfg->module_path[Module::mutator] = this->conf[mutator_path];
		cfg->parameters[Module::mutator] = this->conf[mutator_parameters];
	}

	if (this->conf.find(selector_path) == this->conf.end())
	{
		printf("==> No path was found for the selector module\n");
		exit(-1);
	}
	else
	{
		cfg->module_path[Module::selector] = this->conf[selector_path];
		cfg->parameters[Module::selector] = this->conf[selector_parameters];
	}

	return cfg;
}
