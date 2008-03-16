#include "ConfigIO.h"

using std::ifstream;
using std::ofstream;

void ConfigIO::load(const char *conf_path)
{
}

void ConfigIO::write(const char *conf_path, const char *general, const char *modules)
{
	ofstream conf (conf_path);
	if (conf.is_open())
	{
		conf << "# Don't change the order of these settings!\n"
			<< general
			<< '\n'
			<< modules;
		conf.close();
	}
}
