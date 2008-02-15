#include "PlotterFactory.h"

using std::vector;

PlotterFactory::PlotterFactory(const char *filename, const Config *c, const vector<const char *> *m)
: config(c), modules(m), plotter(0), log_file(filename)
{ }

IPlotter *PlotterFactory::get_plotter()
{
	if (this->plotter == 0)
	{
		if (this->config->plotter.compare("SVG") == 0)
			this->plotter = new Plotter_SVG(this->log_file, this->modules, this->config);
	}
	return this->plotter;
}
