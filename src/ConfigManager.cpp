#include "ConfigManager.h"

using std::ifstream;
using std::string;
using std::vector;

ConfigManager::ConfigManager(const char *cf) : conf_file(cf) { }

const Config ConfigManager::parse()
{
	Config config;
	this->ngene_conf.open(this->conf_file);
	if (this->ngene_conf.is_open())
	{
		config.module_path.assign(Module::number_of_types, "");
		config.parameters.assign(Module::number_of_types, "");

		config.adult_pool_capacity = atoi(get_conf().c_str());
		config.doomsday = atoi(get_conf().c_str());
		if (is_true(get_conf()))
			config.elitism = true;
		else
			config.elitism = false;
		config.lifespan = atoi(get_conf().c_str());
		config.mating_rate = atof(get_conf().c_str());
		config.max_prodigies = atoi(get_conf().c_str()) + 1;
		config.mutation_rate = atof(get_conf().c_str());
		config.offspring_rate = atoi(get_conf().c_str());

		config.module_path[Module::gene] = get_conf();
		config.parameters[Module::gene] = get_conf();

		config.module_path[Module::fitness] = get_conf();
		config.parameters[Module::fitness] = get_conf();

		config.module_path[Module::mating] = get_conf();
		config.parameters[Module::mating] = get_conf();

		config.module_path[Module::mutator] = get_conf();
		config.parameters[Module::mutator] = get_conf();

		config.module_path[Module::selector] = get_conf();
		config.parameters[Module::selector] = get_conf();

		config.plotter = "SVG";

		this->ngene_conf.close();
	}
	else
		throw "Failed to open configuration file.";

	return config;
}

string ConfigManager::get_conf()
{
	string tmp;
	do
	{
		getline(this->ngene_conf, tmp);
		boost::algorithm::trim(tmp);
	} while (tmp.size() == 0 || tmp[0] == '#');
	return tmp;
}

bool ConfigManager::is_true(const string &b)
{
	if (b[0] == '1'
		|| ((b[0] == 'T' || b[0] == 't')
			&& (b[1] == 'R' || b[1] == 'r')
			&& (b[2] == 'U' || b[2] == 'u')
			&& (b[3] == 'E' || b[3] == 'e')))
		return true;
	else
		return false;
}
