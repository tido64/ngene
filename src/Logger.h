#if WIN32
#	define WIN32_LEAN_AND_MEAN
#	include <direct.h>
#else
#	include <sys/stat.h>
#endif

/// Logger takes care of properly logging every run. A log consists of a plot
/// or graph, and an actual output of the fittest individual after an ended
/// run. The outputs produced are typically stored with the following file
/// names:
/// - 20071220-201435.svg    (plot/graph)
/// - 20071220-201435.output (best fit individual)
///
/// where the file name follows YYYYMMdd-hhmmss (ie. date, then time).

#include <cerrno>
#include <cstring>
#include <ctime>
#include <limits>
#include "PlotterFactory.h"
#include "Plugins.h"

class Logger
{
public:
	Logger();
	~Logger();

	/// Starts the log with some information about this run, ie. modules loaded
	/// and configuration.
	/// \param modules  The list of modules loaded
	/// \param config   The configuration
	void log(const Config *config, const std::vector<const char *> &modules);

	/// Logs the progression of the run for each generation.
	/// \param generation  The current generation
	/// \param population  The current population
	/// \return Returns true if a perfect specimen was found
	bool log(const unsigned int generation, const Population &);

	/// Towards the end of a run, another file is created to output the
	/// solutions found. In the current implementation, only the best is
	/// actually written to file. Additionally, the log outputs the time spent
	/// on current run.
	/// \param best  The best speicmen in the population
	/// \param time  The time spent on this run
	void log(const char *best, double time);

private:
	char timestamp[64];	///< The time at which this run started
	IPlotter *plotter;	///< A pointer to the plotter
};
