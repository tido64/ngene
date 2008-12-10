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

class ConfigManager
{
public:
	ConfigManager(const char *config_file)
	{
		std::ifstream in_cfg (config_file);
		if (!in_cfg.is_open())
		{
			printf("==> Failed to open file: %s\n", config_file);
			exit(-1);
		}

		unsigned int comment, equal_sign;
		std::string line, section;
		while (!in_cfg.eof())
		{
 			std::getline(in_cfg, line);
			ngene::trim(line);
			if (line[0] != '#')
			{
				if (line[0] == '[')
				{
					section = line.substr(1, line.find_first_of(']') - 1);
					section += ':';
				}
				else
				{
					equal_sign = line.find_first_of('=');
					if (equal_sign != std::string::npos)
					{
						comment = line.find_first_of('#');

						std::string key = line.substr(0, equal_sign++);
						ngene::trim(key);
						key = section + key;

						std::string val = line.substr(equal_sign, comment - equal_sign);
						ngene::trim(val);

						this->conf[key] = val;
					}
				}
			}
		}
		in_cfg.close();
	}

	/// Parses the configuration file and returns a config object.
	const void *parse();

private:
	std::map<std::string, std::string> conf;

	/// Dumps the configuration file. For debugging purposes only.
	void dump()
	{
		printf("==> Dumping configuration file...\n");
		for (std::map<std::string, std::string>::const_iterator i = conf.begin(); i != conf.end(); i++)
			printf("==> %s = %s\n", i->first.c_str(), i->second.c_str());
	}
};

#endif
