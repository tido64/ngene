/// The interface used by Logger to plot the progression graph. It will contain
/// the details of the current run, as well as a graph of the progression of
/// the population. The name of the output file is typically the date and time
/// the run was initiated.

#ifndef PLOTTER_INTERFACE
#define PLOTTER_INTERFACE

#include "Config.h"

class IPlotter
{
public:
	virtual ~IPlotter() { };

	/// Initiates the plotter and starts outputting the details for this run.
	/// \param filename The path to the output
	/// \param modules The list of modules loaded
	/// \param config The configuration
	virtual bool initiate(std::string filename, const std::vector<const char *> &modules, const Config &config) = 0;

	/// Plots the progression for each generation.
	/// \param generation The current generation
	/// \param min The lowest fitness of current generation
	/// \param avg The average fitness of current generation
	/// \param max The highest fitness of current generation
	virtual void plot(const unsigned int generation, double min, double avg, double max) = 0;
};

#endif
