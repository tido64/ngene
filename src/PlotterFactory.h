/// Creates (lazy) and returns an instance (implementation) of IPlotter. Used
/// by Logger to create graphs as part of the log.

#include "Plotter_SVG.h"

class PlotterFactory
{
public:
	PlotterFactory(const char *filename, const std::vector<const char *> *modules, const Config *config);

	/// Creates an instance of a plotter, given its type. Once created, the
	/// pointer to this instance is returned on subsequent calls.
	/// \param type The plotter to create/return
	//IPlotter *create_plotter(const std::string &type);
	IPlotter *get_plotter();

private:
	const Config *config;
	const std::vector<const char *> *modules;
	IPlotter *plotter;
	std::string log_file;
};
