#include "Ngene.h"

using std::sort;
using std::string;
using std::vector;

const char *NGENE_VERSION = "1.1.81024";

int main(int argc, char *argv[])
{
	InterruptHandler interrupt_handler;

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
	printf("Starting Ngene v%s\n", NGENE_VERSION);

	// Load configuration
	ConfigManager *config_manager = new ConfigManager(config_file.c_str());
	const Config *config = static_cast<const Config *>(config_manager->parse());
	delete config_manager;
	config_manager = 0;

	// Load all plugins
	PluginManager module (config);

	// Initialize logging
	Logger logger;
	logger.log(config, module.modules);

	// Initialize constants and containers
	const bool
		elitism = config->elitism;
	const unsigned int
		capacity = config->capacity,
		doomsday = config->doomsday,
		lifespan = config->lifespan,
		offspring_rate = config->offspring_rate,
		prodigies = config->prodigies;
	double
		mating_rate = config->mating_rate,
		mutation_rate = config->mutation_rate,
		time;
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

	// Prepare the initial population
	{
		Specimen specimen;
		specimen.age = 1;
		for (unsigned int i = 0; i < capacity; i++)
		{
			specimen.genotype.clear();
			module.seed(specimen.genotype);
			module.assess_fitness(specimen);
			adults.push_back(specimen);
		}
		module.seed = 0;
	}

	printf("Evolution started: %i generations shall live and prosper!\n\n", doomsday);

	logger.log(1, adults);
	time = clock();

	// Commence evolution
	for (unsigned int generation = 2; generation <= doomsday; generation++)
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

			if (Random::Instance().next() <= mating_rate)
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
		#pragma omp parallel for
		for (int i = 0; i < static_cast<int>(offspring.size()); i++)
		{
			if (Random::Instance().next() <= mutation_rate)
				module.mutate(offspring[i].genotype);
			module.assess_fitness(offspring[i]);
			offspring[i].age = 0;
		}

		if (lifespan > 1)
		{
			Population::iterator iter_tmp, start = adults.begin();
			if (elitism)
			{
				sort(adults.begin(), adults.end());
				start = adults.begin() + 1;
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
					? Random::Instance().next_int(offspring.size()) : Random::Instance().next_int(prodigies);
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
		}
		else
		{
			if (elitism) // replace worst fit offspring with best fit adult
				*worst_specimen(offspring.begin(), offspring.end()) = *best_specimen(adults.begin(), adults.end());
			adults.swap(offspring);
		}

		// Terminate if a perfect specimen is found or user canceled
		if (logger.log(generation, adults))
		{
			printf("Perfect specimen found. ");
			break;
		}
		else if (USER_INTERVENTION)
			break;
	}
	time = clock() - time;
	logger.log(module.genotype_to_str(best_specimen(adults.begin(), adults.end())->genotype), time);
	return 0;
}
