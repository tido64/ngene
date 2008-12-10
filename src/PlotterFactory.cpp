#include "PlotterFactory.h"

using std::vector;

IPlotter *PlotterFactory::get_plotter(char *filename, const Config *c, const vector<const char *> *m)
{
	static IPlotter *plotter = 0;
	if (plotter == 0)
	{
		if (c->plotter.compare("SVG") == 0)
			plotter = new Plotter_SVG(filename, m, c);
		else
			plotter = new Plotter_Dummy();
	}
	return plotter;
}
