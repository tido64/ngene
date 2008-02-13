#include <algorithm>
#include <boost/any.hpp>

#include "ConfigManager.h"
#include "Organism.h"

class Synthesizer
{
public:
	Synthesizer();
	DNA synthesize();

private:
	const ConfigManager config;
	Random mt_rand;
	std::string species;

	std::vector<double> generate_protein_parameters(unsigned int n, const std::pair<double, double> *stimuli);
	std::vector<double> generate_speciation_parameters(const std::pair<double, double> *stimuli);
	boost::dynamic_bitset<> generate_transcription_promoter(unsigned int length);
};
