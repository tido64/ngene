/// A structure storing the configuration. This structure is used by
/// ConfigManager, but should be accessible by the whole system once the
/// ConfigManager object is instantiated.

#ifndef CONFIG_STRUCT
#define CONFIG_STRUCT

#include <string>
#include <vector>

struct Config
{
	bool elitism;							///< Elitism carries the most fit adult over to the next generation
	double mating_rate,						///< The rate of a successful mating
		mutation_rate;						///< The rate of mutation
	unsigned int adult_pool_capacity,		///< Maximum number of adults per generation
		doomsday,							///< Number of generations
		lifespan,							///< Number of generations an adult will live
		max_prodigies,						///< Number of prodigies replacing adults when lifespan > 1
		offspring_rate;						///< Number of offspring produced each generation
	std::string plotter;					///< The name of the plotter used
	std::vector<std::string> module_path,	///< The path to the modules loaded
		parameters;							///< The parameters for each module
};

#endif