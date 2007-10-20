#include "Ngene.h"

using namespace std;
using boost::any;
using boost::mt19937;

const char *NGENE_VERSION = "0.2007.10.19";

int main()
{
	printf("Starting Ngene v%s\n\nPreparing the environment:\n", NGENE_VERSION);

	SettingsManager settings_manager;
	if (!settings_manager.is_loaded())
	{
		printf("  * Could not read from 'ngene.conf'.\n\nAborting...\n");
		return -1;
	}

	PluginManager module (settings_manager);

	Logger logger;
	logger.log(module.modules);

	boost::mt19937 rand_gen ((unsigned)time(NULL));
	//boost::uniform_01<boost::mt19937> rand_dist (rand_gen);
	//boost::variate_generator<boost::mt19937 &, boost::uniform_01<boost::mt19937> > mt_rand (rand_gen, rand_dist);
	boost::uniform_real<double> rand_dist (0, 1);
	boost::variate_generator<boost::mt19937 &, boost::uniform_real<double> > mt_rand (rand_gen, rand_dist);

	// Prepare the initial population
	double population_fitness = 0;
	multiset<Specimen> adults;
	for (int i = 0; i < settings_manager.config.adult_pool_capacity; i++)
	{
		Specimen specimen;
		specimen.age = 1;
		module.seed(specimen.genotype);
		module.fitness_assess(specimen);
		population_fitness += specimen.fitness;
		adults.insert(specimen);
	}

	vector<multiset<Specimen>::iterator> mates (settings_manager.config.adult_pool_capacity);
	multiset<Specimen> offspring;
	multiset<Specimen>::iterator iter_tmp;

	printf("Evolution started: %i generations shall live and prosper!\n\n", settings_manager.config.doomsday);

	logger.log(0, adults.rbegin()->fitness, population_fitness / adults.size(), adults.begin()->fitness);
	double ticks = clock();

	// Commence evolution
	for (int generation = 1; generation < settings_manager.config.doomsday; generation++)
	{
		// Mating season!
		offspring.clear();
		if ((int)mates.size() < 2)
		{
			iter_tmp = --adults.end();
			mates.push_back(iter_tmp);
			mates.push_back(iter_tmp);
		}
		// The following loop has multithreading potential. Exploit!
		while ((int)offspring.size() < settings_manager.config.offspring_rate)
		{
			do
			{
				module.select(mates[0], adults, generation);
				module.select(mates[1], adults, generation);
			} while (mates[0] == mates[1]);
			if (mt_rand() <= settings_manager.config.mating_rate)
			{
				vector<Specimen> embryo (module.offspring_rate);
				module.mate(embryo, *mates[0], *mates[1]);
				for(vector<Specimen>::iterator fetus = embryo.begin(); fetus != embryo.end(); fetus++)
				{
					if (mt_rand() <= settings_manager.config.mutation_rate)
						module.mutate(fetus->genotype);
					module.fitness_assess(*fetus);
					offspring.insert(*fetus);
				}
			}
		}

		// Replace the adults with offspring
		if (settings_manager.config.lifespan == 0)
		{
			if (settings_manager.config.elitism)
			{
				Specimen specimen = *adults.begin();
				adults = offspring;
				adults.insert(specimen);
			}
			else
				adults = offspring;
		}
		else	// Age the adult pool and replace offspring with old adults
		{
			mates.clear();
			for (multiset<Specimen>::iterator i = --adults.end(); i != adults.begin(); i--)
			{
				if(i->age == settings_manager.config.lifespan)
					mates.push_back(i);
				else
					i->age++;
			}
			if (!settings_manager.config.elitism)
			{
				iter_tmp = adults.begin();
				if(iter_tmp->age == settings_manager.config.lifespan)
					adults.erase(iter_tmp);
				else
					iter_tmp->age++;
			}
			if ((int)mates.size() > 0)
			{
				for (vector<multiset<Specimen>::iterator>::iterator i = mates.begin(); i != mates.end(); i++)
					adults.erase(*i);
				for (int i = (int)adults.size(); i != settings_manager.config.adult_pool_capacity; i++)
				{
					module.select(iter_tmp, offspring, generation);
					adults.insert(*iter_tmp);
					offspring.erase(iter_tmp);
				}
			}

			// Replace lower citizens with prodigies
			for (int i = 0; i < (int)(mt_rand() * settings_manager.config.max_prodigies); i++)
			{
				adults.erase(--adults.end());
				module.select(iter_tmp, offspring, generation);
				adults.insert(*iter_tmp);
				offspring.erase(iter_tmp);
			}
		}

		// Gather statistics
		population_fitness = 0;
		for (multiset<Specimen>::iterator i = adults.begin(); i != adults.end(); i++)
			population_fitness += i->fitness;
		logger.log(generation, adults.rbegin()->fitness, population_fitness / adults.size(), adults.begin()->fitness);
	}
	ticks = clock() - ticks;

	logger.log(adults, module.genotype_to_str);

	mates.clear();
	adults.clear();
	offspring.clear();

	logger.log(ticks);
	return 0;
}

