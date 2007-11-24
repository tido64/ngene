#include "IPlotter.h"
#include "Plotter_SVG.h"

class PlotterFactory
{
public:
	PlotterFactory();
	IPlotter *create_plotter(std::string type);

private:
	IPlotter *plotter;
};
