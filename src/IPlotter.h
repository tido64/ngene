#ifndef PLOTTER_INTERFACE
#define PLOTTER_INTERFACE

#include "Config.h"

class IPlotter
{
public:
	virtual ~IPlotter() { };
	virtual bool initiate(std::string filename, const std::vector<const char *> &modules, const Config &config) = 0;
	virtual void plot(const unsigned int generation, double min, double avg, double max) = 0;
};

#endif
