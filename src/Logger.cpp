#include "Logger.h"

using std::string;

Logger::Logger()
{
	boost::filesystem::create_directory("logs");
	const std::time_t now = time(NULL);
	strftime(this->timestamp, sizeof(this->timestamp), "./logs/%Y%m%d-%H%M%S", localtime(&now));
	this->log_file = fopen(this->timestamp, "w");
}

void Logger::log(std::vector<const char *> &modules)
{
	fprintf(this->log_file, "# %s\n", this->timestamp);

	this->title = (char *)modules[gene_module];
	printf("  * Species:           %s\n", modules[gene_module]);
	fprintf(this->log_file, "# Species:           %s\n", modules[gene_module]);

	printf("  * Fitness assessor:  %s\n", modules[fitness_module]);
	fprintf(this->log_file, "# Fitness assessor:  %s\n", modules[fitness_module]);

	printf("  * Mating style:      %s\n", modules[mating_module]);
	fprintf(this->log_file, "# Mating style:      %s\n", modules[mating_module]);

	printf("  * Mutator:           %s\n", modules[mutator_module]);
	fprintf(this->log_file, "# Mutator:           %s\n", modules[mutator_module]);

	printf("  * Selector:          %s\n\n", modules[selector_module]);
	fprintf(this->log_file, "# Selector:          %s\n\n", modules[selector_module]);
}

void Logger::log(const int generation, const double min, const double avg, const double max)
{
	printf(" %i:\tmin: %.4f\tavg: %.4f\tmax: %.4f\n", generation, min, avg, max);
	this->log_min += boost::lexical_cast<string>(min) + "\n";
	this->log_avg += boost::lexical_cast<string>(avg) + "\n";
	this->log_max += boost::lexical_cast<string>(max) + "\n";
}

void Logger::log(const std::multiset<Specimen> &population, GenotypeToStr genotype_to_str)
{
	fprintf(this->log_file, "%s\n\n", this->log_max.c_str());
	fprintf(this->log_file, "%s\n\n", this->log_min.c_str());
	fprintf(this->log_file, "%s\n\n", this->log_avg.c_str());

	std::multiset<Specimen>::const_iterator top = population.begin();
	printf("\n  * Model specimen: %s\n\n", genotype_to_str(top->genotype));
	fputs("# Model specimen:\n", this->log_file);
	fprintf(this->log_file, "# %s\n", genotype_to_str(top->genotype));
	fclose(this->log_file);

	fopen("last_run.gp", "w");
	fprintf(this->log_file,
		"set xlabel 'generation'\nset ylabel 'fitness'\n\nset autoscale x\nset yrange [0:1]\n\nset term png small size 480,320\n\nset key outside\nset key box\nset output '%s.png'\nset title '%s'\nset key title 'Legend'\nset style data linespoints\nplot '%s' index 0 title 'max', '%s' index 1 title 'min', '%s' index 2 title 'avg'",
		this->timestamp,
		this->title,
		this->timestamp,
		this->timestamp,
		this->timestamp);
	fclose(this->log_file);

	system("gnuplot last_run.gp");
}

void Logger::log(double ticks)
{
	ticks /= CLOCKS_PER_SEC;
	printf("Completed in %i minute(s) and %i second(s).\n\n", (int)(ticks / 60), (int)ticks);
}

