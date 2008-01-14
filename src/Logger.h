/// Logger takes care of properly logging every run. A log consists of a plot
/// or graph, and an actual output of the fittest individual after an ended
/// run. The outputs produced are typically stored with the following file
/// names:
/// - 20071220-201435.svg		(plot/graph)
/// - 20071220-201435.output	(best fit individual)
///
/// where the file name follows YYYYMMdd-hhmmss (ie. date, then time).

#include <set>
#include <boost/filesystem.hpp>

#include "Interfaces/Specimen.h"
#include "PlotterFactory.h"

class Logger
{
	/// \see PluginManager::GenotypeToStr
	typedef const char *(*GenotypeToStr)(const std::vector<boost::any> &);

public:
	Logger();
	~Logger();

	/// Starts the log with some information about this run, ie. modules loaded
	/// and configuration.
	/// \param modules The list of modules loaded
	/// \param config The configuration
	void log(const std::vector<const char *> &modules, const Config &config);

	/// Logs the progression of the run for each generation.
	/// \param generation The current generation
	/// \param min The lowest fitness of current generation
	/// \param avg The average fitness of current generation
	/// \param max The highest fitness of current generation
	void log(const unsigned int generation, const double min, const double avg, const double max);

	/// Towards the end of a run, another file is created to output the
	/// solutions found. In the current implementation, only the best is
	/// actually written to file.
	/// \param population The population of the last generation
	/// \param genotype_to_str A pointer to a function that converts a genotype to string
	void log(const std::multiset<Specimen> &population, GenotypeToStr genotype_to_str);

	/// Logs the time used for this run.
	/// \param ticks The ticks accumulated for this run.
	void log(double ticks);

private:
	char timestamp[64];	///< The time at which this run started
	IPlotter *plotter;	///< A pointer to the plotter
};
