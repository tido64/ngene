#include <set>
#include <boost/filesystem.hpp>

#include "Interfaces/Specimen.h"
#include "PlotterFactory.h"

class Logger
{
	typedef const char *(*GenotypeToStr)(const std::vector<boost::any> &);

public:
	Logger();
	~Logger();
	void log(std::vector<const char *> &modules, const Config &config);
	void log(const unsigned int generation, const double min, const double avg, const double max);
	void log(const std::multiset<Specimen> &population, GenotypeToStr genotype_to_str);
	void log(double ticks);

private:
	char timestamp[64];
	IPlotter *plotter;
};
