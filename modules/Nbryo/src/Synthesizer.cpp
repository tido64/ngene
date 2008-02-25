#include "Synthesizer.h"

using std::pair;
using std::random_shuffle;
using std::string;
using std::vector;

Synthesizer::Synthesizer()
{
	srand((unsigned int)time(0));
}

DNA Synthesizer::synthesize()
{
	DNA dna;
	dna.reserve(this->config.number_of_genes);

	boost::dynamic_bitset<> sequence (this->config.gene_sequence_length);
	boost::dynamic_bitset<> promoter (this->config.promoter_length);
	vector<double> thresholds (this->config.number_of_hormones, 0.0);
	vector<CellType::Type> neighbours (Direction::number_of_directions, CellType::any);
	vector<double> parameters;
	const pair<double, double> *stimuli = 0;

	for (unsigned int i = 0; i < this->config.number_of_genes; i++)
	{
		// Create gene sequence
		for (unsigned int b = 0; b < this->config.gene_sequence_length; b++)
			sequence[b] = this->mt_rand.next() < 0.5;

		ProteinType::Type protein_type = static_cast<ProteinType::Type>(this->mt_rand.next_int(ProteinType::number_of_types));

		// Initiate hormonal thresholds (most of these values will be low to ease development)
		for (unsigned int h = 0; h < this->config.number_of_hormones; h++)
			thresholds[h] = (this->mt_rand.next() < 0.5) ? 0.0 : this->mt_rand.next() / 10.0;

		// Initiate conditions for a thriving neighbourhood
		for (unsigned int n = 0; n < this->config.number_of_dont_care_neighbours; n++)
			neighbours[n] = CellType::any;
		for (unsigned int n = this->config.number_of_dont_care_neighbours; n < Direction::number_of_directions; n++)
			neighbours[n] = static_cast<CellType::Type>(this->mt_rand.next_int(CellType::empty, this->config.number_of_cell_types));
		random_shuffle(neighbours.begin(), neighbours.end());

		dna.push_back(Gene(
			sequence,
			protein_type,
			this->mt_rand.next_int(this->config.protein_lifespan),
			thresholds,
			neighbours,
			this->config.number_of_cell_types));

		switch (protein_type)
		{
			case ProteinType::mitotic:
				stimuli = this->config.get_protein_stimuli(protein_type);
				generate_protein_parameters(parameters, Direction::number_of_directions, stimuli);
				dna.rbegin()->ergo_proxy(parameters, stimuli);
				break;
			case ProteinType::regulatory:
				stimuli = this->config.get_protein_stimuli(protein_type);
				generate_protein_parameters(parameters, this->config.number_of_hormones, stimuli);
				dna.rbegin()->ergo_proxy(parameters, stimuli);
				break;
			case ProteinType::speciation:
				parameters.clear();
				parameters.push_back(this->mt_rand.next_int(this->config.number_of_cell_types));
				stimuli = this->config.get_protein_stimuli(protein_type);
				parameters.push_back(this->mt_rand.next(stimuli->first, stimuli->second));
				dna.rbegin()->ergo_proxy(parameters, stimuli);
				break;
			case ProteinType::transcribing:
				for (unsigned int i = 0; i < this->config.promoter_length; i++)
					promoter[i] = this->mt_rand.next() < 0.5;
				dna.rbegin()->ergo_proxy(promoter);
				break;
			default:
				exit(-1);
		}
	}
	return dna;
}

void Synthesizer::generate_protein_parameters(vector<double> &parameters, unsigned int n, const pair<double, double> *stimuli)
{
	double factor = stimuli->second - stimuli->first;
	parameters.clear();
	for (unsigned int p = 0; p < n; p++)
		parameters.push_back((this->mt_rand.next() < 0.5) ? 0.0 : this->mt_rand.next() * factor + stimuli->first);
}
