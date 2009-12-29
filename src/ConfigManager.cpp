#include "ConfigManager.h"

using std::getline;
using std::ifstream;
using std::map;
using std::string;

Config *ConfigManager::load(const char *config_file)
{
	ifstream in_cfg (config_file);
	if (!in_cfg.is_open())
		return 0;

	unsigned int comment, equal_sign;
	string line, section;
	map<string, string> conf_map;
	while (!in_cfg.eof())
	{
		getline(in_cfg, line);
		line = ngene::trim(line);
		if (line[0] == '#')
			continue;
		if (line[0] == '[')
		{
			section = line.substr(1, line.find_first_of(']') - 1);
			section += ':';
		}
		else
		{
			equal_sign = line.find_first_of('=');
			if (equal_sign != string::npos)
			{
				comment = line.find_first_of('#');

				string key = line.substr(0, equal_sign++);
				key = section + ngene::trim(key);

				string val = line.substr(equal_sign, comment - equal_sign);
				conf_map[key] = ngene::trim(val);
			}
		}
	}
	in_cfg.close();

	bool incomplete = false;
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
		plotter				= "plotter",
		prodigies			= "prodigies",
		selector_parameters	= "selector:parameters",
		selector_path		= "selector:path";

	if (conf_map.find(genotype_path) == conf_map.end())
	{
		incomplete = true;
		puts("==> [FAIL] No path was found for a genotype module");
	}
	if (conf_map.find(fitness_path) == conf_map.end())
	{
		incomplete = true;
		puts("==> [FAIL] No path was found for a fitness module");
	}
	if (conf_map.find(mating_path) == conf_map.end())
	{
		incomplete = true;
		puts("==> [FAIL] No path was found for a mating module");
	}
	if (conf_map.find(mutator_path) == conf_map.end())
	{
		incomplete = true;
		puts("==> [FAIL] No path was found for a mutator module");
	}
	if (conf_map.find(selector_path) == conf_map.end())
	{
		incomplete = true;
		puts("==> [FAIL] No path was found for a selector module");
	}
	if (incomplete) return 0;

	Config *conf = new Config();

	if (conf_map.find(capacity) == conf_map.end())
	{
		conf->capacity = 100;
		printf("==> [WARN] No value for for '%s' found, using default: %u\n", capacity.c_str(), conf->capacity);
	}
	else
		conf->capacity = atoi(conf_map[capacity].c_str());

	if (conf_map.find(generations) == conf_map.end())
	{
		conf->doomsday = 50;
		printf("==> [WARN] No value for for '%s' found, using default: %u\n", generations.c_str(), conf->doomsday);
	}
	else
		conf->doomsday = atoi(conf_map[generations].c_str());

	if (conf_map.find(elitism) == conf_map.end())
	{
		conf->elitism = false;
		printf("==> [WARN] No value for for '%s' found, using default: false\n", elitism.c_str());
	}
	else
		conf->elitism = (atoi(conf_map[elitism].c_str()) == 1) ? true : false;

	if (conf_map.find(mating_rate) == conf_map.end())
	{
		conf->mating_rate = 0.9;
		printf("==> [WARN] No value for for '%s' found, using default: %.2f\n", mating_rate.c_str(), conf->mating_rate);
	}
	else
		conf->mating_rate = atof(conf_map[mating_rate].c_str());

	if (conf_map.find(mutation_rate) == conf_map.end())
	{
		conf->mutation_rate = 0.2;
		printf("==> [WARN] No value for for '%s' found, using default: %.2f\n", mutation_rate.c_str(), conf->mutation_rate);
	}
	else
		conf->mutation_rate = atof(conf_map[mutation_rate].c_str());

	if (conf_map.find(offspring_rate) == conf_map.end())
	{
		conf->offspring_rate = static_cast<unsigned int>(conf->capacity + conf->capacity * 0.1);
		printf("==> [WARN] No value for for '%s' found, using default: %u\n", offspring_rate.c_str(), conf->offspring_rate);
	}
	else
		conf->offspring_rate = atoi(conf_map[offspring_rate].c_str());

	if (conf_map.find(plotter) != conf_map.end())
		conf->plotter = conf_map[plotter];

#ifdef ENABLE_LIFESPAN
	if (conf_map.find(lifespan) == conf_map.end())
	{
		conf->lifespan = 1;
		printf("==> [WARN] No value for for '%s' found, using default: %u\n", lifespan.c_str(), conf->lifespan);
	}
	else
		conf->lifespan = atoi(conf_map[lifespan].c_str());

	if (conf_map.find(prodigies) == conf_map.end())
	{
		conf->prodigies = static_cast<unsigned int>(conf->capacity * 0.3);
		printf("==> [WARN] No value for for '%s' found, using default: %u\n", prodigies.c_str(), conf->prodigies);
	}
	else
		conf->prodigies = atoi(conf_map[prodigies].c_str());
#endif

	conf->module_path.assign(Module::number_of_types, empty);
	conf->parameters.assign(Module::number_of_types, empty);
	conf->module_path[Module::gene] = conf_map[genotype_path];
	conf->parameters[Module::gene] = conf_map[genotype_parameters];
	conf->module_path[Module::fitness] = conf_map[fitness_path];
	conf->parameters[Module::fitness] = conf_map[fitness_parameters];
	conf->module_path[Module::mating] = conf_map[mating_path];
	conf->parameters[Module::mating] = conf_map[mating_parameters];
	conf->module_path[Module::mutator] = conf_map[mutator_path];
	conf->parameters[Module::mutator] = conf_map[mutator_parameters];
	conf->module_path[Module::selector] = conf_map[selector_path];
	conf->parameters[Module::selector] = conf_map[selector_parameters];

	return conf;
}
