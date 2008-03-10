#include <algorithm>
#include <boost/any.hpp>

#include "ConfigManager.h"
#include "Organism.h"

class Synthesizer
{
public:
	Synthesizer();
	void synthesize(std::vector<boost::any> &genotype);

private:
	const ConfigManager config;
	std::string species;

	void generate_protein_parameters(std::vector<double> &parameters, unsigned int n, const std::pair<double, double> *stimuli);
};
