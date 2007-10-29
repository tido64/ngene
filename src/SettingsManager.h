#ifndef SETTINGS_MANAGER
#define SETTINGS_MANAGER

#include <fstream>
#include <vector>
#include <boost/algorithm/string/trim.hpp>

#include "ModuleType.h"

struct Configuration
{
	bool elitism;
	double mating_rate, mutation_rate;
	int adult_pool_capacity,
		doomsday,
		lifespan,
		max_prodigies,
		offspring_rate;
	std::vector<std::string> module_path, parameters;
};

class SettingsManager
{
public:
	Configuration config;
	SettingsManager(const char *conf_file);
	bool is_loaded();

private:
	bool loaded;
	std::ifstream ngene_conf;
	std::string get_setting();
};

#endif

