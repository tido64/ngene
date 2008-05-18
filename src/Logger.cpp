#include "Logger.h"

Logger::Logger() : plotter(0)
{
#if WIN32
	if (_mkdir("logs") == - 1 && errno != EEXIST)
#else
	if (mkdir("logs", 0775) == -1 && errno != EEXIST)
#endif
	{
		printf("  * Failed to create directory for logs: %s\n", strerror(errno));
		abort();
	}
	const std::time_t now = time(0);
	strftime(this->timestamp, sizeof(this->timestamp), "./logs/%Y%m%d-%H%M%S", localtime(&now));
}

Logger::~Logger()
{
	delete this->plotter;
}

void Logger::log(const Config &config, const std::vector<const char *> &modules)
{
	PlotterFactory plotter_factory ((const char *)&this->timestamp, &config, &modules);
	this->plotter = plotter_factory.get_plotter();

	printf("  * Species:           %s\n", modules[Module::gene]);
	printf("  * Fitness assessor:  %s\n", modules[Module::fitness]);
	printf("  * Mating style:      %s\n", modules[Module::mating]);
	printf("  * Mutator:           %s\n", modules[Module::mutator]);
	printf("  * Selector:          %s\n\n", modules[Module::selector]);
}

bool Logger::log(const unsigned int generation, const Population &pop)
{
	double
		avg = 0.0,
		max = 0.0,
		min = std::numeric_limits<double>::max();

	for (Population::const_iterator i = pop.begin(); i != pop.end(); i++)
	{
		if (i->fitness > max)
			max = i->fitness;
		else if (i->fitness < min)
			min = i->fitness;
		avg += i->fitness;
	}
	avg /= pop.size();

	this->plotter->plot(generation, min, avg, max);
	printf(" %i:\tmin: %.4f\tavg: %.4f\tmax: %.4f\n", generation, min, avg, max);
	return max == 1.0;
}

void Logger::log(const Specimen &best, GenotypeToStr *genotype_to_str, double time)
{
	std::ofstream output (strcat(this->timestamp, ".output"));
	output << (*genotype_to_str)(best.genotype) << "\n";
	output.close();

	printf("Completed in %i minute(s) and %i second(s).\n\n",
		static_cast<int>(time / 60), static_cast<int>(time + 0.5) % 60);
}
