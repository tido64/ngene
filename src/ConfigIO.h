//#include <cstdio>
#include <fstream>

class ConfigIO
{
public:
	static void load(const char *conf_path);
	static void write(const char *conf_path, const char *general, const char *modules);
};
