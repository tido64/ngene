/// An implementation of IPlotter that outputs nothing.

#include "IPlotter.h"

class Plotter_Dummy : public IPlotter
{
public:
	bool open(std::string filename, const Config *config, const std::vector<const char *> *modules) { return true; }
	void plot(unsigned int generation, double min, double avg, double max) { }
};
