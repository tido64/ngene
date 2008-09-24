#include "Ngene.h"

using std::sort;
using std::string;
using std::vector;

const char *NGENE_VERSION = "0.1.1 (build/20080922)";

int main(int argc, char *argv[])
{
	string config_file ("ngene.conf");
	if (argc > 1)
	{
		if ((strcmp(argv[1], "--help") == 0) | (strcmp(argv[1], "-h") == 0))
		{
			printf("Usage: %s [config file]\n", argv[0]);
			return 0;
		}
		else
			config_file = argv[1];
	}

	printf("Starting Ngene v%s\n\nPreparing the environment:\n", NGENE_VERSION);

	// Load configuration
	ConfigManager *config_manager = new ConfigManager(config_file.c_str());
	const Config config = config_manager->parse();
	delete config_manager;
	config_manager = 0;

	// Load all plugins
	PluginManager module (config);

	// Initialize logging
	Logger logger;
	logger.log(config, module.modules);

	double time;	///< Time elapsed since the beginning of execution
	Population
		adults,		///< The adult population
		offspring,	///< The offspring population
		embryo (module.offspring_rate);
	vector<Population::iterator>
		mates;
	mates.reserve(config.adult_pool_capacity);
	adults.reserve(config.adult_pool_capacity);

	// Prepare the initial population
	{
		Specimen specimen;
		specimen.age = 1;
		for (unsigned int i = 0; i < config.adult_pool_capacity; i++)
		{
			specimen.genotype.clear();
			module.seed(specimen.genotype);
			module.assess_fitness(specimen);
			adults.push_back(specimen);
		}
		module.seed = 0;
	}

	printf("Evolution started: %i generations shall live and prosper!\n\n", config.doomsday);

	logger.log(1, adults);
	time = clock();

	// Commence evolution
	for (unsigned int generation = 2; generation <= config.doomsday; generation++)
	{
		// Mating season!
		offspring.clear();
		do
		{
			// Select two *different* specimens for mating
			module.select(mates[0], adults, generation);
			do
			{
				module.select(mates[1], adults, generation);
			} while (mates[0] == mates[1]);

			if (Random::Instance().next() <= config.mating_rate)
			{
				// Empty the embryonic vessels
				for (Population::iterator i = embryo.begin(); i != embryo.end(); i++)
					i->genotype.clear();

				// Make the specimens mate and insert the embryos into the vessels
				module.mate(embryo, *mates[0], *mates[1]);

				// Insert the embryos into the offspring vector for evaluation
				offspring.insert(offspring.end(), embryo.begin(), embryo.end());
			}
		} while (offspring.size() < config.offspring_rate);

		// (Randomly mutate and) assess the fitness of each offspring
		#pragma omp parallel for
		for (int i = 0; i < static_cast<int>(offspring.size()); i++)
		{
			if (Random::Instance().next() <= config.mutation_rate)
				module.mutate(offspring[i].genotype);
			module.assess_fitness(offspring[i]);
			offspring[i].age = 0;
		}

		if (config.lifespan > 1)
		{
			Population::iterator
				iter_tmp,
				start = adults.begin();
			if (config.elitism)
			{
				start++;
				sort(adults.begin(), adults.end());
			}
			for (Population::iterator i = start; i != adults.end(); i++)
			{
				if(i->age >= config.lifespan)
				{
					module.select(iter_tmp, offspring, generation);
					*i = *iter_tmp;
					i->age = 1;
					offspring.erase(iter_tmp);
				}
				else
					i->age++;
			}
			if (config.max_prodigies > 0) // Replace lower citizens with prodigies
			{
				unsigned int prodigies = (config.max_prodigies > offspring.size())
					? Random::Instance().next_int(offspring.size()) : Random::Instance().next_int(config.max_prodigies);
				sort(adults.begin(), adults.end());
				for (unsigned int i = 0; i < prodigies; i++)
					adults.pop_back();
				for (unsigned int i = 0; i < prodigies; i++)
				{
					module.select(iter_tmp, offspring, generation);
					adults.push_back(*iter_tmp);
					adults.rbegin()->age = 1;
					offspring.erase(iter_tmp);
				}
			}
		}
		else
		{
			if (config.elitism) // replace worst fit offspring with best fit adult
				*worst_specimen(offspring.begin(), offspring.end()) = *best_specimen(adults.begin(), adults.end());
			adults.swap(offspring);
		}

		if (logger.log(generation, adults))
		{
			printf("Perfect specimen found. ");
			break;
		}
	}
	time = clock() - time;
	logger.log(*best_specimen(adults.begin(), adults.end()), &module.genotype_to_str, time);
	return 0;
}
