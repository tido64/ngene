/// A common ConfigManager that reads and manages configuration from file.
/// Upon instantiation, it will attempt to open and read the config file
/// specified by the parameter sent to it. Configuration is stored in a map
/// that can be parsed later on by any module.

#ifndef CONFIGMANAGER_H_
#define CONFIGMANAGER_H_

#include <cstdlib>
#include <fstream>
#include <map>

#include <Algorithm.h>

#include "Config.h"
#include "ModuleType.h"

struct ConfigManager
{
	Config *load(const char *config_file);	///< Parses the configuration file and returns a config object.
};

#endif
