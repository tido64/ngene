#include "Ngene.h"

//#define __DEBUG_MODE

using std::vector;

const char *NGENE_VERSION = "0.1 (build 2008-02-20)";

int main(int argc, char *argv[])
{
	ConfigManager *config_manager;
	if (argc > 1)
	{
		if (strcmp(argv[1], "--config") == 0)
		{
			printf("Starting Ngene v%s\n  * Running with configuration file: %s\n\nPreparing the environment:\n", NGENE_VERSION, argv[2]);
			config_manager = new ConfigManager(argv[2]);
		}
		else
		{
			printf("Usage: %s [--config <config file>]\n", argv[0]);
			return 0;
		}
	}
	else
	{
		printf("Starting Ngene v%s\n\nPreparing the environment:\n", NGENE_VERSION);
		config_manager = new ConfigManager("ngene.conf");
	}

#ifdef __DEBUG_MODE
	printf("[Ngene.cpp] Loading configuration ... ");
#endif

	// Load configuration
	const Config config = config_manager->parse();
	delete config_manager;
	config_manager = 0;

#ifdef __DEBUG_MODE
	printf("done!\n[Ngene.cpp] Loading plugins ... ");
#endif

	// Load all plugins
	PluginManager module (config);

#ifdef __DEBUG_MODE
	printf("done!\n[Ngene.cpp] Initializing logger ... \n");
#endif

	// Initialize logging
	Logger logger;
	logger.log(config, module.modules);

#ifdef __DEBUG_MODE
	printf("[Ngene.cpp] Logger initialized!\n[Ngene.cpp] Initiating program and initial population ... ");
#endif

	double
		population_fitness = 0,		///< The population's accumulated fitness
		ticks;						///< Number of ticks elapsed since the beginning of execution
	Population
		*adults = new Population(),	///< The adult population
		*offspring;					///< The offspring population
	Population::iterator
		iter_tmp;					///< A temporary iterator/pointer to an individual
	vector<Population::iterator>
		mates;

	// Prepare the initial population
	for (unsigned int i = 0; i < config.adult_pool_capacity; i++)
	{
		Specimen specimen;
		specimen.age = 1;
		module.seed(specimen.genotype);
		module.assess_fitness(specimen);
		population_fitness += specimen.fitness;
		adults->insert(specimen);
	}
	mates.reserve(config.adult_pool_capacity);
	module.seed = 0;

#ifdef __DEBUG_MODE
	printf("done!\n\n");
#endif

	printf("Evolution started: %i generations shall live and prosper!\n\n", config.doomsday);

	logger.log(1, adults->rbegin()->fitness, population_fitness / adults->size(), adults->begin()->fitness);
	ticks = clock();

#ifdef __DEBUG_MODE
	printf("[Ngene.cpp] Starting genetic algorithm\n");
#endif

	// Commence evolution
	for (unsigned int generation = 2; generation <= config.doomsday; generation++)
	{
		// Mating season!
		if (mates.size() < 2)
			mates.assign(2, adults->begin());
		offspring = new Population();
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
				vector<Specimen> embryo (module.offspring_rate);
				module.mate(embryo, *mates[0], *mates[1]);
				for (vector<Specimen>::iterator fetus = embryo.begin(); fetus != embryo.end(); fetus++)
				{
					if (Random::Instance().next() <= config.mutation_rate)
						module.mutate(fetus->genotype);
					module.assess_fitness(*fetus);
					offspring->insert(*fetus);
				}
			}
		}

		if (config.lifespan < 2) // replace the adults with offspring
		{
			if (config.elitism)
			{
				offspring->erase(--offspring->end());
				offspring->insert(*adults->begin());
			}
			delete adults;
			adults = offspring;
		}
		else // age the adult pool and replace offspring with old adults
		{
			mates.clear();
			for (Population::iterator i = --adults->end(); i != adults->begin(); i--)
			{
				if(i->age >= config.lifespan)
					mates.push_back(i);
				else
					i->age++;
			}
			if (!config.elitism)
			{
				iter_tmp = adults->begin();
				if(iter_tmp->age >= config.lifespan)
					adults->erase(iter_tmp);
				else
					iter_tmp->age++;
			}
			if (mates.size() > 0)
			{
				for (vector<Population::iterator>::iterator i = mates.begin(); i != mates.end(); i++)
					adults->erase(*i);
				for (unsigned int i = adults->size(); i != config.adult_pool_capacity; i++)
				{
					module.select(iter_tmp, *offspring, generation);
					adults->insert(*iter_tmp)->age = 1;
					offspring->erase(iter_tmp);
				}
			}

			// Replace lower citizens with prodigies
			if (config.max_prodigies > 0)
			{
				for (unsigned int i = 0; i < (config.max_prodigies > offspring->size()) ? Random::Instance().next_int(offspring->size()) : Random::Instance().next_int(config.max_prodigies); i++)
				{
					module.select(iter_tmp, *offspring, generation);
					adults->erase(--adults->end());
					adults->insert(*iter_tmp)->age = 1;
					offspring->erase(iter_tmp);
				}
			}
			delete offspring;
		}

		// Gather statistics
		population_fitness = 0;
		for (Population::iterator i = adults->begin(); i != adults->end(); i++)
			population_fitness += i->fitness;
		logger.log(generation, adults->rbegin()->fitness, population_fitness / adults->size(), adults->begin()->fitness);
	}
	ticks = clock() - ticks;
	logger.log(adults, &module.genotype_to_str);
	logger.log(ticks);
	delete adults;
	return 0;
}
