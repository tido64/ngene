#include "Ngene.h"

using std::sort;
using std::string;
using std::vector;

const char *NGENE_VERSION = "1.1.91229";

int main(int argc, char *argv[])
{
	printf("ngene v%s\n", NGENE_VERSION);

	string config_file ("ngene.conf");
	if (argc > 1)
	{
		if (argv[1][0] == '-')
		{
			printf("Usage: %s [config file]\n", argv[0]);
			return 0;
		}
		config_file = argv[1];
	}

	InterruptHandler interrupt_handler;

	// Load configuration
	Config *config;
	{
		ConfigManager *config_manager = new ConfigManager();
		config = config_manager->load(config_file.c_str());
		delete config_manager;
	}
	if (config == 0)
	{
		printf("==> [FAIL] Could not parse configuration file: %s\n", config_file.c_str());
		return 1;
	}

	// Load all plugins
	PluginManager module;
	if (!module.load(config))
	{
		delete config;
		puts("==> [FAIL] Could not initialize ngene");
		return 1;
	}

	// Initialize logging
	Logger logger;
	if (!logger.log(config, module.modules))
	{
		delete config;
		return 1;
	}

	// Initialize constants and containers
	const bool
		elitism = config->elitism;
	const unsigned int
		capacity = config->capacity,
		doomsday = config->doomsday,
		offspring_rate = config->offspring_rate;
	unsigned long int
		time;
	double
		mating_rate = config->mating_rate,
		mutation_rate = config->mutation_rate;

#ifdef ENABLE_LIFESPAN
	const unsigned int
		lifespan = config->lifespan,
		prodigies = config->prodigies;
#endif

	// We no longer need the configuration
	delete config;
	config = 0;

	Population
		adults,
		offspring,
		embryo (module.offspring_rate);
	vector<Population::iterator>
		mates;
	adults.reserve(capacity);
	mates.reserve(capacity);

	// Prepare initial population
	for (unsigned int i = 0; i < capacity; i++)
	{
		Specimen specimen;
		module.seed(specimen.genotype);
		module.assess_fitness(specimen);
#ifdef ENABLE_LIFESPAN
		specimen.age = 1;
#endif
		adults.push_back(specimen);
	}
	module.seed = 0;

	printf("Evolution started: %u generations shall live and prosper!\n\n", doomsday);

	time = clock();

	// Commence evolution
	for (unsigned int generation = 2; generation <= doomsday; generation++)
	{
		// Terminate if a perfect specimen is found or user canceled
		if (logger.log(generation - 1, adults))
		{
			printf("\nPerfect specimen found. ");
			break;
		}
		if (TERMINATION_PENDING)
			break;

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

			if (module.random->next() <= mating_rate)
			{
				// Empty the embryonic vessels
				for (Population::iterator i = embryo.begin(); i != embryo.end(); i++)
					i->genotype.clear();

				// Make the specimens mate and insert the embryos into the vessels
				module.mate(embryo, *mates[0], *mates[1]);

				// Insert the embryos into the offspring vector for evaluation
				offspring.insert(offspring.end(), embryo.begin(), embryo.end());
			}
		} while (offspring.size() < offspring_rate);

		// (Randomly mutate and) assess the fitness of each offspring
#ifdef _OPENMP
#		pragma omp parallel for
#endif
		for (int i = 0; i < static_cast<int>(offspring.size()); i++)
		{
			if (module.random->next() <= mutation_rate)
				module.mutate(offspring[i].genotype);
			module.assess_fitness(offspring[i]);
#ifdef ENABLE_LIFESPAN
			offspring[i].age = 0;
		}

		Population::iterator iter_tmp, start = adults.begin();
		if (elitism)
		{
			sort(adults.begin(), adults.end());
			start = adults.begin();
			start++;
		}
		for (Population::iterator i = start; i != adults.end(); i++)
		{
			if(i->age >= lifespan)
			{
				module.select(iter_tmp, offspring, generation);
				*i = *iter_tmp;
				i->age = 1;
				offspring.erase(iter_tmp);
			}
			else
				i->age++;
		}
		if (prodigies > 0) // Replace lower citizens with prodigies
		{
			unsigned int current_prodigies = (prodigies > offspring.size())
				? module.random->next_int(offspring.size()) : module.random->next_int(prodigies);
			sort(adults.begin(), adults.end());
			for (unsigned int i = 0; i < current_prodigies; i++)
				adults.pop_back();
			for (unsigned int i = 0; i < current_prodigies; i++)
			{
				module.select(iter_tmp, offspring, generation);
				adults.push_back(*iter_tmp);
				adults.rbegin()->age = 1;
				offspring.erase(iter_tmp);
			}
		}

#else
		}

		if (elitism) // replace worst fit offspring with best fit adult
			iter_swap(worst_specimen(offspring.begin(), offspring.end()), best_specimen(adults.begin(), adults.end()));
		adults.swap(offspring);
#endif
	}
	time = clock() - time;
	logger.log(module.gtoa(best_specimen(adults.begin(), adults.end())->genotype), time);
	return 0;
}
