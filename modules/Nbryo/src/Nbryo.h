#include <boost/any.hpp>
#include <boost/dynamic_bitset.hpp>

#include "ConfigManager.h"
#include "Direction.h"
#include "Organism.h"

class Nbryo
{
public:
	Nbryo();
	DNA synthesize();

private:
	const ConfigManager config;
	std::string species;

	std::vector<double> generate_protein_parameters(unsigned int n, const std::pair<double, double> *stimuli);
	std::vector<double> generate_speciation_parameters(const std::pair<double, double> *stimuli);
	boost::dynamic_bitset<> generate_transcription_promoter(unsigned int length);

	double random() { return (double)rand() / ((double)RAND_MAX + 1.0); }
	int random(int k) { return (int)(random() * k); }
};
