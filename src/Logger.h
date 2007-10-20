#include "ModuleType.h"
#include "Interfaces/Specimen.h"
#include <cstdio>
#include <ctime>
#include <set>
#include <string>
#include <vector>
#include <boost/filesystem.hpp>
#include <boost/lexical_cast.hpp>

class Logger
{
	typedef const char *(*GenotypeToStr)(const std::vector<boost::any> &);

public:
	Logger();
	void log(std::vector<const char *> &modules);
	void log(const int generation, const double min, const double avg, const double max);
	void log(const std::multiset<Specimen> &population, GenotypeToStr genotype_to_str);
	void log(double ticks);

private:
	char timestamp[32];
	char *title;
	FILE *log_file;
	std::string log_avg, log_max, log_min;
};

