#include "Ngene.h"

using std::vector;

const char *NGENE_VERSION = "0.2008.01.31";

int main(int argc, char *argv[])
{
	char *ngene_conf = 0;
	if (argc > 1)
	{
		if (strcmp(argv[1], "--config") == 0)
		{
			printf("Starting Ngene v%s\n\nPreparing the environment:\n  * Running with configuration file: %s\n", NGENE_VERSION, argv[2]);
			ngene_conf = argv[2];
		}
		else
		{
			printf("Usage: Ngene --config <config file>\n");
			return 0;
		}
	}
	else
	{
		printf("Starting Ngene v%s\n\nPreparing the environment:\n", NGENE_VERSION);
		ngene_conf = "ngene.conf";
	}

	// Load configuration
	ConfigManager *config_manager = new ConfigManager(ngene_conf);
	if (!config_manager->is_loaded())
	{
		printf("  * Could not read from '%s'.\n\nAborting...\n", ngene_conf);
		return -1;
	}
	const Config config = config_manager->config;
	delete config_manager;
	config_manager = 0;

	// Load all plugins
	PluginManager module (&config);

	// Initialize logging
	Logger logger;
	try
	{
		logger.log(config, module.modules);
	}
	catch (char *e)
	{
		printf("  * %s\n\nAborting...\n", e);
		return -1;
	}

	// Initialize the mersenne twister random number generator
	boost::mt19937 rand_gen ((unsigned)time(0));
	boost::uniform_real<double> rand_dist (0, 1);
	boost::variate_generator<boost::mt19937 &, boost::uniform_real<double> > mt_rand (rand_gen, rand_dist);

	double
		population_fitness = 0,		///< The population's accumulated fitness
		ticks;						///< Number of ticks elapsed since the beginning of execution
	Population
		*adults = new Population(),	///< The adult population
		*offspring;					///< The offspring population
	Population::iterator
		iter_tmp;					///< A temporary iterator/pointer to an individual
	vector<Population::iterator>
		mates (config.adult_pool_capacity);

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

	printf("Evolution started: %i generations shall live and prosper!\n\n", config.doomsday);

	logger.log(0, adults->rbegin()->fitness, population_fitness / adults->size(), adults->begin()->fitness);
	ticks = clock();

	// Commence evolution
	for (unsigned int generation = 1; generation < config.doomsday; generation++)
	{
		// Mating season!
		if ((int)mates.size() < 2)
		{
			iter_tmp = adults->begin();
			mates.push_back(iter_tmp);
			mates.push_back(iter_tmp);
		}
		offspring = new Population();
		// The following loop has multithreading potential. Exploit!
		while (offspring->size() < config.offspring_rate)
		{
			do
			{
				module.select(mates[0], *adults, generation);
				module.select(mates[1], *adults, generation);
			} while (mates[0] == mates[1]);
			if (mt_rand() <= config.mating_rate)
			{
				vector<Specimen> embryo (module.offspring_rate);
				module.mate(embryo, *mates[0], *mates[1]);
				for (vector<Specimen>::iterator fetus = embryo.begin(); fetus != embryo.end(); fetus++)
				{
					if (mt_rand() <= config.mutation_rate)
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
			if ((int)mates.size() > 0)
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
				for (int i = 0; i < (int)(mt_rand() * config.max_prodigies > offspring->size() ? offspring->size() : config.max_prodigies); i++)
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
	logger.log(*adults, module.genotype_to_str);
	logger.log(ticks);
	delete adults;
	return 0;
}
