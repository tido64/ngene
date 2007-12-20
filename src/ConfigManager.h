/// ConfigManager reads and manages configuration from file. Upon
/// instantiation, it will attempt to open and read the config file specified
/// by the parameter sent to it. It will then populate a Config object that
/// will be publically accessible.

#ifndef CONFIG_MANAGER
#define CONFIG_MANAGER

#include <fstream>
#include <boost/algorithm/string/trim.hpp>

#include "Config.h"
#include "ModuleType.h"

class ConfigManager
{
public:
	Config config;						///< Mapping of the config file read

	/// Starts reading from the config file
	/// \param conf_file The path to the configuration file
	ConfigManager(const char *conf_file);

	bool is_loaded();					///< Returns true if config file loaded fine

private:
	bool loaded;						///< Stores the successfulness of loading and parsing the config file
	std::ifstream ngene_conf;			///< The file stream used to open a config file
	std::string get_conf();				///< Gets the next parameter in a config file
	bool is_true(const std::string &b);	///< Parses a string for a boolean value
};

#endif