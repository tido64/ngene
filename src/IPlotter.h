/// The interface used by Logger to plot the progression graph. It will
/// contain the details of the current run, as well as a graph of the
/// progression of the population. The name of the output file is
/// typically the date and time the run was initiated.

#ifndef IPLOTTER_H_
#define IPLOTTER_H_

#include "Config.h"

class IPlotter
{
public:
	virtual ~IPlotter() { }

	/// Opens the log file and writes some information about current run.
	/// \param filename  The name of the file to write to
	/// \param config    The configuration of current run
	/// \param modules   Vector of loaded modules
	/// \return Returns false on failure
	virtual bool open(std::string filename, const Config *config, const std::vector<const char *> *modules) = 0;

	/// Plots the progression for each generation.
	/// \param generation  The current generation
	/// \param min         The lowest fitness of current generation
	/// \param avg         The average fitness of current generation
	/// \param max         The highest fitness of current generation
	virtual void plot(unsigned int generation, double min, double avg, double max) = 0;
};

#endif
