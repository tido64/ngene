/// Lazy-instantiates and returns an instance (implementation) of IPlotter.
/// Used by Logger to create graphs as part of the log.

#include "Plotter_Dummy.h"
#include "Plotter_SVG.h"

class PlotterFactory
{
public:
	/// Creates an instance of a plotter, given its type. Once created, the
	/// pointer to this instance is returned.
	IPlotter *get_plotter(const std::string &plotter_name);
};
