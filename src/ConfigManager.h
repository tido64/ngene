/// ConfigManager reads and manages configuration from file. Upon
/// instantiation, it will attempt to open and read the config file specified
/// by the parameter sent to it. It will then populate a Config object that
/// will be publically accessible.

#ifndef CONFIGMANAGER_H_
#define CONFIGMANAGER_H_

#include <fstream>
#include <boost/algorithm/string/trim.hpp>

#include "Config.h"
#include "ModuleType.h"

class ConfigManager
{
public:
	ConfigManager(const char *config_file);

	/// Parses the configuration file and returns an config object.
	const Config parse();

private:
	const char *conf_file;
	std::ifstream ngene_conf;	///< The file stream used to open a config file

	/// Gets the next parameter in a config file.
	std::string get_conf();

	/// Parses a string for a boolean value.
	bool is_true(const std::string &b);
};

#endif
