/// A structure storing the configuration. This structure is used by
/// ConfigManager, but should be accessible by the whole system once the
/// ConfigManager object is instantiated.

#ifndef CONFIG_H_
#define CONFIG_H_

#include <string>
#include <vector>

struct Config
{
	bool
		elitism;		///< Elitism carries the most fit adult over to the next generation
	unsigned int
		capacity,		///< Maximum number of adults per generation
		doomsday,		///< Number of generations
		offspring_rate;	///< Number of offspring produced each generation

#ifdef ENABLE_LIFESPAN

	unsigned int
		lifespan,		///< Number of generations an adult will live
		prodigies;		///< Number of prodigies replacing adults when lifespan > 1

#endif

	double
		mating_rate,	///< The rate of a successful mating
		mutation_rate;	///< The rate of mutation
	std::string
		plotter;		///< The name of the plotter used
	std::vector<std::string>
		module_path,	///< The path to the modules loaded
		parameters;		///< The parameters for each module
};

#endif
