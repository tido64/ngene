#include "ConfigManager.h"

using std::ifstream;
using std::string;
using std::vector;
using boost::algorithm::trim;

ConfigManager::ConfigManager(const char *conf_file)
{
	this->ngene_conf.open(conf_file);
	this->loaded = false;
	if (ngene_conf.is_open())
	{
		this->config.module_path = vector<string> (number_of_modules);
		this->config.parameters = vector<string> (number_of_modules);

		this->config.adult_pool_capacity = atoi(get_conf().c_str());
		this->config.doomsday = atoi(get_conf().c_str());
		if (get_conf().compare(0, 4, "true") == 0)
			this->config.elitism = true;
		else
			this->config.elitism = false;
		this->config.lifespan = atoi(get_conf().c_str());
		this->config.mating_rate = atof(get_conf().c_str());
		this->config.max_prodigies = atoi(get_conf().c_str()) + 1;
		this->config.mutation_rate = atof(get_conf().c_str());
		this->config.offspring_rate = atoi(get_conf().c_str());

		this->config.module_path[gene_module] = get_conf();
		this->config.parameters[gene_module] = get_conf();

		this->config.module_path[fitness_module] = get_conf();
		this->config.parameters[fitness_module] = get_conf();

		this->config.module_path[mating_module] = get_conf();
		this->config.parameters[mating_module] = get_conf();

		this->config.module_path[mutator_module] = get_conf();
		this->config.parameters[mutator_module] = get_conf();

		this->config.module_path[selector_module] = get_conf();
		this->config.parameters[selector_module] = get_conf();

		this->config.plotter = "SVG";

		this->loaded = true;
		this->ngene_conf.close();
	}
}

string ConfigManager::get_conf()
{
	string tmp;
	do
	{
		getline(this->ngene_conf, tmp);
		trim(tmp);
	} while (tmp.size() == 0 || tmp[0] == '#');
	return tmp;
}

bool ConfigManager::is_loaded()
{
	return this->loaded;
}
