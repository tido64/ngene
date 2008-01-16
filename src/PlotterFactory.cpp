#include "PlotterFactory.h"

using std::vector;

PlotterFactory::PlotterFactory(const char *filename, const vector<const char *> *m, const Config *c)
	: modules(m), config(c)
{
	this->log_file = filename;
	this->plotter = NULL;
}

IPlotter *PlotterFactory::get_plotter()
{
	if (this->plotter == NULL)
	{
		if (this->config->plotter.compare("SVG") == 0)
			this->plotter = new Plotter_SVG(this->log_file, this->modules, this->config);
	}
	return this->plotter;
}
