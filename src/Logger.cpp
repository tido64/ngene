#include "Logger.h"

using std::ofstream;
using std::string;
using std::vector;

Logger::Logger() : plotter(0), filename("./logs/") { }

Logger::~Logger()
{
	delete this->plotter;
}

bool Logger::log(const unsigned int generation, const Population &pop)
{
	double
		avg = 0.0,
		max = 0.0,
		min = 1.0;

	for (Population::const_iterator i = pop.begin(); i != pop.end(); ++i)
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
	this->filename += ".output";
	ofstream output (this->filename.c_str());
	output << best << "\n";
	output.close();

	time /= CLOCKS_PER_SEC;
	printf("\nCompleted in %lu minute(s) and %lu second(s).\n", time / 60, time % 60);
}

bool Logger::start(const Config *config, const vector<const char *> &modules)
{
#ifdef WIN32
	if (_mkdir("logs") == - 1 && errno != EEXIST)
#else
	if (mkdir("logs", 0775) == -1 && errno != EEXIST)
#endif
	{
		const size_t sz = 256;
		char buf[sz];
		printf("==> [FAIL] Could not create directory for logs: %s\n", strerror_r(errno, buf, sz));
		return false;
	}

	// Get the local time
	const time_t now = time(0);
	struct tm t;
	localtime_r(&now, &t);
	char buf[16];  // I doubt anyone would use this in the year 10,000+
	strftime(buf, sizeof(buf), "%Y%m%d-%H%M%S", &t);
	this->filename += buf;

	// Initialise the plotter and use the timestamp as file name
	PlotterFactory plotter_factory;
	this->plotter = plotter_factory.get_plotter(config->plotter);
	if (!this->plotter->open(this->filename, config, &modules))
	{
		puts("==> [FAIL] Could not initiate plotter. Please make sure you have writing privileges.");
		return false;
	}

	printf("  * Species:           %s\n  * Fitness assessor:  %s\n  * Mating style:      %s\n  * Mutator:           %s\n  * Selector:          %s\n\n",
		modules[Module::gene],
		modules[Module::fitness],
		modules[Module::mating],
		modules[Module::mutator],
		modules[Module::selector]);
	return true;
}
