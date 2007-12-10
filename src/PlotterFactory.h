#include "IPlotter.h"
#include "Plotter_SVG.h"

class PlotterFactory
{
public:
	PlotterFactory();
	~PlotterFactory();
	IPlotter *create_plotter(const std::string &type);

private:
	IPlotter *plotter;
};
