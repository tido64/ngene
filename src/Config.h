#ifndef CONFIG_STRUCT
#define CONFIG_STRUCT

#include <string>
#include <vector>

struct Config
{
	bool elitism;
	double mating_rate, mutation_rate;
	unsigned int adult_pool_capacity,
		doomsday,
		lifespan,
		max_prodigies,
		offspring_rate;
	std::string plotter;
	std::vector<std::string> module_path, parameters;
};

#endif
