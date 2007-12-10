#include <fstream>
#include "IPlotter.h"
#include "ModuleType.h"
#include "Config.h"

class Plotter_SVG : public IPlotter
{
public:
	~Plotter_SVG();
	bool initiate(char *filename, const std::vector<const char *> &modules, const Config &config);
	void plot(const unsigned int generation, double min, double avg, double max);

private:
	double avg, fitness_margin, fitness_scale, max, min;
	std::ofstream svg;
	std::vector<double> generation_axis;
};
