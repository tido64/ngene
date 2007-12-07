#include "PlotterFactory.h"

using std::string;

PlotterFactory::PlotterFactory()
{
	this->plotter = NULL;
}

IPlotter *PlotterFactory::create_plotter(string type)
{
	if (this->plotter == NULL)
	{
		if (type.compare("SVG") == 0)
			this->plotter = new Plotter_SVG();
	}
	return this->plotter;
}
