#include "Ngene.h"

using std::sort;
using std::vector;

const char *NGENE_VERSION = "0.1.1 (build/20080401)";

int main(int argc, char *argv[])
{
	ConfigManager *config_manager;
	if (argc > 1)
	{
		if (strcmp(argv[1], "--config") == 0)
			config_manager = new ConfigManager(argv[2]);
		else
		{
			printf("Usage: %s [--config <config file>]\n", argv[0]);
			return 0;
		}
	}
	else
		config_manager = new ConfigManager("ngene.conf");

	printf("Starting Ngene v%s\n\nPreparing the environment:\n", NGENE_VERSION);

	// Load configuration
	const Config config = config_manager->parse();
	delete config_manager;
	config_manager = 0;

	// Load all plugins
	PluginManager module (config);

	// Initialize logging
	Logger logger;
	logger.log(config, module.modules);

	double
		population_fitness = 0,		///< The population's accumulated fitness
		population_max = 0,			///< The population's max fitness
		population_min = std::numeric_limits<double>::max(),	///< The population's min fitness
		ticks;						///< Number of ticks elapsed since the beginning of execution
	Population
		*adults = new Population(),	///< The adult population
		*offspring,					///< The offspring population
		embryo (module.offspring_rate);
	vector<Population::iterator>
		mates;
	mates.reserve(config.adult_pool_capacity);
	adults->reserve(config.adult_pool_capacity);

	// Prepare the initial population
	Specimen specimen;
	specimen.age = 1;
	for (unsigned int i = 0; i < config.adult_pool_capacity; i++)
	{
		specimen.genotype.clear();
		module.seed(specimen.genotype);
		module.assess_fitness(specimen);
		adults->push_back(specimen);

		if (specimen.fitness > population_max)
			population_max = specimen.fitness;
		if (specimen.fitness < population_min)
			population_min = specimen.fitness;
		population_fitness += specimen.fitness;
	}
	module.seed = 0;

	printf("Evolution started: %i generations shall live and prosper!\n\n", config.doomsday);

	logger.log(1, population_min, population_fitness / adults->size(), population_max);
	ticks = clock();

	// Commence evolution
	for (unsigned int generation = 2; generation <= config.doomsday; generation++)
	{
		// Mating season!
		offspring = new Population();
		offspring->reserve(config.offspring_rate);
		// The following loop has multithreading potential. Exploit!
		while (offspring->size() < config.offspring_rate)
		{
			do
			{
				module.select(mates[0], *adults, generation);
				module.select(mates[1], *adults, generation);
			} while (mates[0] == mates[1]);
			if (Random::Instance().next() <= config.mating_rate)
			{
				for (Population::iterator i = embryo.begin(); i != embryo.end(); i++)
					i->genotype.clear();
				module.mate(embryo, *mates[0], *mates[1]);
				for (vector<Specimen>::iterator fetus = embryo.begin(); fetus != embryo.end(); fetus++)
				{
					if (Random::Instance().next() <= config.mutation_rate)
						module.mutate(fetus->genotype);
					module.assess_fitness(*fetus);
					fetus->age = 0;
					offspring->push_back(*fetus);
				}
			}
		}

		if (config.lifespan < 2) // replace the adult population with its offspring
		{
			if (config.elitism) // replace worst fit offspring with best fit adult
				*worst_specimen(offspring->begin(), offspring->end()) = *best_specimen(adults->begin(), adults->end());
			delete adults;
			adults = offspring;
			offspring = 0;
		}
		else // age the adult pool and replace offspring with old adults
		{
			Population::iterator iter_tmp, start;
			if (!config.elitism)
				start = adults->begin();
			else
			{
				sort(adults->begin(), adults->end());
				start = adults->begin() + 1;
			}
			for (Population::iterator i = start; i != adults->end(); i++)
			{
				if(i->age >= config.lifespan)
				{
					module.select(iter_tmp, *offspring, generation);
					*i = *iter_tmp;
					i->age = 1;
					offspring->erase(iter_tmp);
				}
				else
					i->age++;
			}
			if (config.max_prodigies > 0) // Replace lower citizens with prodigies
			{
				unsigned int prodigies = (config.max_prodigies > offspring->size())
					? Random::Instance().next_int(offspring->size()) : Random::Instance().next_int(config.max_prodigies);
				sort(adults->begin(), adults->end());
				for (unsigned int i = 0; i < prodigies; i++)
					adults->pop_back();
				for (unsigned int i = 0; i < prodigies; i++)
				{
					module.select(iter_tmp, *offspring, generation);
					adults->push_back(*iter_tmp);
					adults->rbegin()->age = 1;
					offspring->erase(iter_tmp);
				}
			}
			delete offspring;
		}

		// Gather statistics
		population_min = std::numeric_limits<double>::max();
		population_fitness = population_max = 0;
		for (Population::iterator i = adults->begin(); i != adults->end(); i++)
		{
			if (i->fitness > population_max)
				population_max = i->fitness;
			if (i->fitness < population_min)
				population_min = i->fitness;
			population_fitness += i->fitness;
		}
		logger.log(generation, population_min, population_fitness / adults->size(), population_max);
		if (population_max == 1.0)
		{
			printf("Perfect specimen found. ");
			break;
		}
	}
	ticks = clock() - ticks;
	logger.log(*best_specimen(adults->begin(), adults->end()), &module.genotype_to_str);
	logger.log(ticks);
	delete adults;
	return 0;
}
