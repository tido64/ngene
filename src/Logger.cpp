#include "Logger.h"

Logger::Logger()
{
	boost::filesystem::create_directory("logs");
	const std::time_t now = time(0);
	strftime(this->timestamp, sizeof(this->timestamp), "./logs/%Y%m%d-%H%M%S", localtime(&now));
	this->plotter = 0;
}

Logger::~Logger()
{
	delete this->plotter;
}

void Logger::log(const Config &config, const std::vector<const char *> &modules)
{
	PlotterFactory plotter_factory ((const char *)&this->timestamp, &config, &modules);
	this->plotter = plotter_factory.get_plotter();
	if (this->plotter->fail())
		throw "Failed to initiate plotter. Make sure you have writing privileges.";

	printf("  * Species:           %s\n", modules[Module::gene]);
	printf("  * Fitness assessor:  %s\n", modules[Module::fitness]);
	printf("  * Mating style:      %s\n", modules[Module::mating]);
	printf("  * Mutator:           %s\n", modules[Module::mutator]);
	printf("  * Selector:          %s\n\n", modules[Module::selector]);
}

void Logger::log(const unsigned int generation, const double min, const double avg, const double max)
{
	this->plotter->plot(generation, min, avg, max);
	printf(" %i:\tmin: %.4f\tavg: %.4f\tmax: %.4f\n", generation, min, avg, max);
}

void Logger::log(const Population &population, GenotypeToStr genotype_to_str)
{
	std::ofstream output (strcat(this->timestamp, ".output"));
	output << genotype_to_str(population.begin()->genotype) << "\n";
	output.close();
}

void Logger::log(double ticks)
{
	ticks /= CLOCKS_PER_SEC;
	printf("Completed in %i minute(s) and %i second(s).\n\n", (int)(ticks / 60), (int)ticks);
}
