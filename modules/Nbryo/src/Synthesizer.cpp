#include "Synthesizer.h"

using std::min;
using std::pair;
using std::random_shuffle;
using std::string;
using std::vector;

Synthesizer::Synthesizer() { }

void Synthesizer::synthesize(vector<boost::any> &genotype)
{
	boost::dynamic_bitset<>
		sequence (this->config.gene_sequence_length),
		promoter (this->config.promoter_length);

	vector<CellType::Type>
		neighbours (Direction::number_of_directions, CellType::any);

	vector<double>
		thresholds (this->config.number_of_hormones, 0.0),
		parameters;

	const pair<double, double> *stimuli = 0;

	genotype.reserve(this->config.number_of_genes);

	for (unsigned int i = 0; i < this->config.number_of_genes; i++)
	{
		// Create gene sequence
		for (unsigned int b = 0; b < this->config.gene_sequence_length; b++)
			sequence[b] = Random::Instance().next() < 0.5;

		ProteinType::Type protein_type = static_cast<ProteinType::Type>(Random::Instance().next_int(ProteinType::number_of_types));

		// Initiate hormonal thresholds (most of these values will be low to ease development)
		for (unsigned int h = 0; h < this->config.number_of_hormones; h++)
			thresholds[h] = (Random::Instance().next() < 0.5) ? 0.0 : Random::Instance().next() / 10.0;

		// Initiate conditions for a thriving neighbourhood
		for (unsigned int n = 0; n < min(this->config.number_of_dont_care_neighbours, static_cast<unsigned int>(Direction::number_of_directions)); n++)
			neighbours[n] = CellType::any;
		for (unsigned int n = this->config.number_of_dont_care_neighbours; n < Direction::number_of_directions; n++)
			neighbours[n] = static_cast<CellType::Type>(Random::Instance().next_int(CellType::empty, this->config.number_of_cell_types));
		random_shuffle(neighbours.begin(), neighbours.end(), Random::Instance());

		Gene g = Gene(
			sequence,
			protein_type,
			Random::Instance().next_int(this->config.protein_lifespan),
			thresholds,
			neighbours,
			this->config.number_of_cell_types);

		switch (protein_type)
		{
			case ProteinType::mitotic:
				stimuli = this->config.get_protein_stimuli(protein_type);
				generate_protein_parameters(parameters, Direction::number_of_directions, stimuli);
				g.ergo_proxy(parameters, stimuli);
				break;
			case ProteinType::regulatory:
				stimuli = this->config.get_protein_stimuli(protein_type);
				generate_protein_parameters(parameters, this->config.number_of_hormones, stimuli);
				g.ergo_proxy(parameters, stimuli);
				break;
			case ProteinType::speciation:
				parameters.clear();
				parameters.push_back(Random::Instance().next_int(this->config.number_of_cell_types));
				stimuli = this->config.get_protein_stimuli(protein_type);
				parameters.push_back(Random::Instance().next(stimuli->first, stimuli->second));
				g.ergo_proxy(parameters, stimuli);
				break;
			case ProteinType::transcribing:
				for (unsigned int i = 0; i < this->config.promoter_length; i++)
					promoter[i] = Random::Instance().next() < 0.5;
				g.ergo_proxy(promoter);
				break;
			default:
				exit(-1);
		}

		genotype.push_back(g);
	}
}

void Synthesizer::generate_protein_parameters(vector<double> &parameters, unsigned int n, const pair<double, double> *stimuli)
{
	double factor = stimuli->second - stimuli->first;
	parameters.clear();
	for (unsigned int p = 0; p < n; p++)
		parameters.push_back((Random::Instance().next() < 0.5) ? 0.0 : Random::Instance().next() * factor + stimuli->first);
}