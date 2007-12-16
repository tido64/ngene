#include "Ngene.h"

using std::multiset;
using std::vector;

const char *NGENE_VERSION = "0.2007.12.16";

int main(int argc, char *argv[])
{
	char *ngene_conf = NULL;
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

	ConfigManager config_manager (ngene_conf);
	if (!config_manager.is_loaded())
	{
		printf("  * Could not read from '%s'.\n\nAborting...\n", ngene_conf);
		return -1;
	}

	PluginManager module (config_manager.config);

	Logger logger;
	try
	{
		logger.log(module.modules, config_manager.config);
	}
	catch (char *e)
	{
		printf("  * %s\n\nAborting...\n", e);
		return -1;
	}

	boost::mt19937							rand_gen ((unsigned)time(NULL));
	//boost::uniform_01<boost::mt19937>		rand_dist (rand_gen);
	//boost::variate_generator<boost::mt19937 &, boost::uniform_01<boost::mt19937> > mt_rand (rand_gen, rand_dist);
	boost::uniform_real<double>				rand_dist (0, 1);
	boost::variate_generator<boost::mt19937 &, boost::uniform_real<double> > mt_rand (rand_gen, rand_dist);
	double									population_fitness = 0, ticks;
	multiset<Specimen>						*adults, *offspring;
	multiset<Specimen>::iterator			iter_tmp;
	vector<multiset<Specimen>::iterator>	mates (config_manager.config.adult_pool_capacity);

	// Prepare the initial population
	adults = new multiset<Specimen>();
	for (unsigned int i = 0; i < config_manager.config.adult_pool_capacity; i++)
	{
		Specimen specimen;
		specimen.age = 1;
		module.seed(specimen.genotype);
		module.fitness_assess(specimen);
		population_fitness += specimen.fitness;
		adults->insert(specimen);
	}

	printf("Evolution started: %i generations shall live and prosper!\n\n", config_manager.config.doomsday);

	logger.log(0, adults->rbegin()->fitness, population_fitness / adults->size(), adults->begin()->fitness);
	ticks = clock();

	// Commence evolution
	for (unsigned int generation = 1; generation < config_manager.config.doomsday; generation++)
	{
		// Mating season!
		if ((int)mates.size() < 2)
		{
			iter_tmp = adults->begin();
			mates.push_back(iter_tmp);
			mates.push_back(iter_tmp);
		}
		offspring = new multiset<Specimen>();
		// The following loop has multithreading potential. Exploit!
		while (offspring->size() < config_manager.config.offspring_rate)
		{
			do
			{
				module.select(mates[0], *adults, generation);
				module.select(mates[1], *adults, generation);
			} while (mates[0] == mates[1]);
			if (mt_rand() <= config_manager.config.mating_rate)
			{
				vector<Specimen> embryo (module.offspring_rate);
				module.mate(embryo, *mates[0], *mates[1]);
				for (vector<Specimen>::iterator fetus = embryo.begin(); fetus != embryo.end(); fetus++)
				{
					if (mt_rand() <= config_manager.config.mutation_rate)
						module.mutate(fetus->genotype);
					module.fitness_assess(*fetus);
					offspring->insert(*fetus);
				}
			}
		}

		// Replace the adults with offspring
		if (config_manager.config.lifespan < 2)
		{
			if (config_manager.config.elitism)
				offspring->insert(*adults->begin());
			delete adults;
			adults = offspring;

			// Truncate the adult population (necessary ?)
			for (unsigned int i = adults->size(); i > config_manager.config.adult_pool_capacity; i--)
				adults->erase(--adults->end());
		}
		else	// Age the adult pool and replace offspring with old adults
		{
			mates.clear();
			for (multiset<Specimen>::iterator i = --adults->end(); i != adults->begin(); i--)
			{
				if(i->age >= config_manager.config.lifespan)
					mates.push_back(i);
				else
					i->age++;
			}
			if (!config_manager.config.elitism)
			{
				iter_tmp = adults->begin();
				if(iter_tmp->age >= config_manager.config.lifespan)
					adults->erase(iter_tmp);
				else
					iter_tmp->age++;
			}
			if ((int)mates.size() > 0)
			{
				for (vector<multiset<Specimen>::iterator>::iterator i = mates.begin(); i != mates.end(); i++)
					adults->erase(*i);
				for (unsigned int i = adults->size(); i != config_manager.config.adult_pool_capacity; i++)
				{
					module.select(iter_tmp, *offspring, generation);
					adults->insert(*iter_tmp)->age = 1;
					offspring->erase(iter_tmp);
				}
			}

			// Replace lower citizens with prodigies
			if (config_manager.config.max_prodigies > 0)
			{
				unsigned int n = config_manager.config.max_prodigies;
				if (n > offspring->size())
					n = offspring->size();
				for (int i = 0; i < (int)(mt_rand() * n); i++)
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
		for (multiset<Specimen>::iterator i = adults->begin(); i != adults->end(); i++)
			population_fitness += i->fitness;
		logger.log(generation, adults->rbegin()->fitness, population_fitness / adults->size(), adults->begin()->fitness);
	}
	ticks = clock() - ticks;
	logger.log(*adults, module.genotype_to_str);
	logger.log(ticks);
	delete adults;
	return 0;
}
