#ifndef CONFIG_MANAGER
#define CONFIG_MANAGER

#include <fstream>
#include <boost/algorithm/string/trim.hpp>

#include "Config.h"
#include "ModuleType.h"

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
	bool is_true(const std::string &b);
};

#endif
