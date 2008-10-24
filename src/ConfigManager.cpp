#include "ConfigManager.h"
#include "Config.h"
#include "ModuleType.h"

using std::map;
using std::string;

const void *ConfigManager::parse()
{
	Config *cfg (new Config());

	if (this->conf.find("capacity") == this->conf.end())
		cfg->capacity = 100;
	else
		cfg->capacity = atoi(this->conf["capacity"].c_str());

	if (this->conf.find("generations") == this->conf.end())
		cfg->doomsday = 50;
	else
		cfg->doomsday = atoi(this->conf["generations"].c_str());

	if (this->conf.find("elitism") == this->conf.end())
		cfg->elitism = false;
	else
		cfg->elitism = (atoi(this->conf["elitism"].c_str()) == 1) ? true : false;

	if (this->conf.find("lifespan") == this->conf.end())
		cfg->lifespan = 1;
	else
		cfg->lifespan = atoi(this->conf["lifespan"].c_str());

	if (this->conf.find("mating rate") == this->conf.end())
		cfg->mating_rate = 0.9;
	else
		cfg->mating_rate = atof(this->conf["mating rate"].c_str());

	if (this->conf.find("mutation rate") == this->conf.end())
		cfg->mutation_rate = 0.2;
	else
		cfg->mutation_rate = atof(this->conf["mutation rate"].c_str());

	if (this->conf.find("offspring rate") == this->conf.end())
		cfg->offspring_rate = static_cast<unsigned int>(cfg->capacity + cfg->capacity * 0.1);
	else
		cfg->offspring_rate = atoi(this->conf["offspring rate"].c_str());

	if (this->conf.find("prodigies") == this->conf.end())
		cfg->prodigies = static_cast<unsigned int>(cfg->capacity * 0.3);
	else
		cfg->prodigies = atoi(this->conf["prodigies"].c_str());

	cfg->module_path.assign(Module::number_of_types, "");
	cfg->parameters.assign(Module::number_of_types, "");

	if (this->conf.find("genotype:path") == this->conf.end())
	{
		printf("==> No path was found for the genotype module\n");
		exit(-1);
	}
	else
	{
		cfg->module_path[Module::gene] = this->conf["genotype:path"];
		cfg->parameters[Module::gene] = this->conf["genotype:parameters"];
	}

	if (this->conf.find("fitness:path") == this->conf.end())
	{
		printf("==> No path was found for the fitness module\n");
		exit(-1);
	}
	else
	{
		cfg->module_path[Module::fitness] = this->conf["fitness:path"];
		cfg->parameters[Module::fitness] = this->conf["fitness:parameters"];
	}

	if (this->conf.find("mating:path") == this->conf.end())
	{
		printf("==> No path was found for the mating module\n");
		exit(-1);
	}
	else
	{
		cfg->module_path[Module::mating] = this->conf["mating:path"];
		cfg->parameters[Module::mating] = this->conf["mating:parameters"];
	}

	if (this->conf.find("mutator:path") == this->conf.end())
	{
		printf("==> No path was found for the mutator module\n");
		exit(-1);
	}
	else
	{
		cfg->module_path[Module::mutator] = this->conf["mutator:path"];
		cfg->parameters[Module::mutator] = this->conf["mutator:parameters"];
	}

	if (this->conf.find("selector:path") == this->conf.end())
	{
		printf("==> No path was found for the selector module\n");
		exit(-1);
	}
	else
	{
		cfg->module_path[Module::selector] = this->conf["selector:path"];
		cfg->parameters[Module::selector] = this->conf["selector:parameters"];
	}

	return cfg;
}
