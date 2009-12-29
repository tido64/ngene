/// An implementation of IPlotter that outputs SVG files.

#include <fstream>
#include "IPlotter.h"
#include "ModuleType.h"

class Plotter_SVG : public IPlotter
{
public:
	Plotter_SVG();
	~Plotter_SVG();
	bool open(std::string filename, const Config *config, const std::vector<const char *> *modules);
	void plot(unsigned int generation, double min, double avg, double max);

private:
	double avg, fitness_margin, fitness_scale, max, min;
	std::ofstream svg;
	std::vector<double> generation_axis;
};
