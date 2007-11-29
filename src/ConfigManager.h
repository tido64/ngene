#ifndef CONFIG_MANAGER
#define CONFIG_MANAGER

#include <fstream>
#include <vector>
#include <boost/algorithm/string/trim.hpp>

#include "ModuleType.h"
#include "Config.h"

class ConfigManager
{
public:
	Config config;
	ConfigManager(const char *conf_file);
	bool is_loaded();

private:
	bool loaded;
	std::ifstream ngene_conf;
	std::string get_conf();
};

#endif
