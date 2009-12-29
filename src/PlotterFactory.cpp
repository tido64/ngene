#include "PlotterFactory.h"

using std::vector;

IPlotter *PlotterFactory::get_plotter(const std::string &plotter_name)
{
	static IPlotter *plotter = 0;
	if (plotter == 0)
	{
		if (plotter_name.compare("SVG") == 0)
			plotter = new Plotter_SVG();
		else
			plotter = new Plotter_Dummy();
	}
	return plotter;
}
