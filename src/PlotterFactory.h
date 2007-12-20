/// Creates and returns an instance (implementation) of IPlotter. Used by
/// Logger to create graphs as part of the log.

#include "Plotter_SVG.h"

class PlotterFactory
{
public:
	PlotterFactory();

	/// Creates an instance of a plotter, given its type. Returns a pointer to
	/// the instance once it is made.
	/// \param type The plotter to create/return
	IPlotter *create_plotter(const std::string &type);

private:
	IPlotter *plotter;
};
