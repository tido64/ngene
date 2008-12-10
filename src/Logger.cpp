#include "Logger.h"

using std::numeric_limits;
using std::ofstream;
using std::vector;

Logger::Logger() : plotter(0)
{
#ifdef WIN32
	if (_mkdir("logs") == - 1 && errno != EEXIST)
#else
	if (mkdir("logs", 0775) == -1 && errno != EEXIST)
#endif
	{
		printf("==> Failed to create directory for logs: %s\n", strerror(errno));
		exit(-1);
	}
	const time_t now = time(0);
	strftime(this->timestamp, sizeof(this->timestamp), "./logs/%Y%m%d-%H%M%S", localtime(&now));
}

Logger::~Logger()
{
	delete this->plotter;
}

void Logger::log(const Config *config, const vector<const char *> &modules)
{
	this->plotter = PlotterFactory::get_plotter(this->timestamp, config, &modules);
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
		min = numeric_limits<double>::max();

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
	printf("\r %u:\tavg: %.4f\tmax: %.4f", generation, avg, max);
	fflush(stdout);
	return max >= 1;
}

void Logger::log(const char *best, unsigned long int time)
{
	ofstream output (strcat(this->timestamp, ".output"));
	output << best << "\n";
	output.close();

	time /= CLOCKS_PER_SEC;
	printf("\nCompleted in %lu minute(s) and %lu second(s).\n", time / 60, time % 60);
}
