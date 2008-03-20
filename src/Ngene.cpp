#include "Ngene.h"

using std::max_element;
using std::min_element;
using std::sort;
using std::vector;

const char *NGENE_VERSION = "0.1 (build/20080320)";

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
		population_min = 0,			///< The population's min fitness
		ticks;						///< Number of ticks elapsed since the beginning of execution
	Population
		*adults = new Population(),	///< The adult population
		*offspring;					///< The offspring population
	Population::iterator
		iter_tmp;					///< A temporary iterator/pointer to an individual
	vector<Population::iterator>
		mates;
	adults->reserve(config.adult_pool_capacity);
	mates.reserve(config.adult_pool_capacity);

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
		else if (specimen.fitness < population_min)
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
		if (mates.size() < 2)
			mates.assign(2, adults->begin());
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
				vector<Specimen> embryo (module.offspring_rate);
				module.mate(embryo, *mates[0], *mates[1]);
				for (vector<Specimen>::iterator fetus = embryo.begin(); fetus != embryo.end(); fetus++)
				{
					if (Random::Instance().next() <= config.mutation_rate)
						module.mutate(fetus->genotype);
					module.assess_fitness(*fetus);
					offspring->push_back(*fetus);
				}
			}
		}

		if (config.lifespan < 2) // replace the adult population with its offspring
		{
			if (config.elitism)
			{
				offspring->erase(min_element(offspring->begin(), offspring->end()));
				offspring->push_back(*max_element(adults->begin(), adults->end()));
			}
			delete adults;
			adults = offspring;
		}
		else // age the adult pool and replace offspring with old adults
		{
			if (!config.elitism)
			{
				iter_tmp = adults->begin();
				if(iter_tmp->age >= config.lifespan)
					adults->erase(iter_tmp);
				else
					iter_tmp->age++;
			}
			else
				sort(adults->begin(), adults->end());
			mates.clear();
			for (Population::iterator i = --adults->end(); i != adults->begin(); i--)
			{
				if(i->age >= config.lifespan)
					mates.push_back(i);
				else
					i->age++;
			}
			if (mates.size() > 0)
			{
				for (vector<Population::iterator>::iterator i = mates.begin(); i != mates.end(); i++)
					adults->erase(*i);
				for (unsigned int i = adults->size(); i < config.adult_pool_capacity; i++)
				{
					module.select(iter_tmp, *offspring, generation);
					adults->push_back(*iter_tmp);
					(--adults->end())->age = 1;
					offspring->erase(iter_tmp);
				}
			}

			// Replace lower citizens with prodigies
			if (config.max_prodigies > 0)
			{
				unsigned int prodigies = (config.max_prodigies > offspring->size()) ? Random::Instance().next_int(offspring->size()) : Random::Instance().next_int(config.max_prodigies);
				sort(adults->begin(), adults->end());
				for (unsigned int i = 0; i < prodigies; i++)
				{
					module.select(iter_tmp, *offspring, generation);
					adults->erase(--adults->end());
					adults->push_back(*iter_tmp);
					(--adults->end())->age = 1;
					offspring->erase(iter_tmp);
				}
			}
			delete offspring;
		}

		// Gather statistics
		population_fitness = 0;
		for (Population::iterator i = adults->begin(); i != adults->end(); i++)
		{
			if (specimen.fitness > population_max)
				population_max = specimen.fitness;
			else if (specimen.fitness < population_min)
				population_min = specimen.fitness;
			population_fitness += i->fitness;
		}
		logger.log(generation, population_min, population_fitness / adults->size(), population_max);
	}
	ticks = clock() - ticks;
	logger.log(adults, &module.genotype_to_str);
	logger.log(ticks);
	delete adults;
	return 0;
}
