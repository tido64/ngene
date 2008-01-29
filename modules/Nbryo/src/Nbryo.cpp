#include "Nbryo.h"

using std::pair;
using std::string;
using std::vector;

Nbryo::Nbryo() { }

DNA Nbryo::synthesize()
{
	DNA dna (this->config.number_of_genes);
	for (unsigned int i = 0; i < this->config.number_of_genes; i++)
	{
		// Create gene sequence
		boost::dynamic_bitset<> sequence (this->config.promoter_length);
		for (unsigned int b = 0; b < this->config.promoter_length; b++)
			sequence[i] = NUtility::random() < 0.5;

		// Initiate hormonal thresholds (most of these values will be low to ease development)
		vector<double> thresholds (this->config.number_of_hormones);
		for (unsigned int h = 0; h < this->config.number_of_hormones; h++)
		{
			if (NUtility::random() < 0.5)
				thresholds.push_back(0.0);
			else
				thresholds.push_back(NUtility::random() / 10.0);
		}

		// Initiate conditions for a thriving neighbourhood
		vector<CellType::Type> neighbours;
		neighbours.reserve(Direction::number_of_directions);
		for (unsigned int i = 0; i < this->config.number_of_dont_care_neighbours; i++)
			neighbours.push_back(CellType::number_of_types);
		for (unsigned int i = this->config.number_of_dont_care_neighbours; i < Direction::number_of_directions; i++)
			neighbours.push_back((CellType::Type)((int)NUtility::random(CellType::number_of_types + 2) - 1));

		// The gene codes for the following protein
		ProteinType::Type protein_type = (ProteinType::Type)NUtility::random(ProteinType::number_of_types);

		// Pre-translate the gene (generate the protein's promoter or parameters)
		switch (protein_type)
		{
			case ProteinType::mitotic:
				dna.push_back(Gene(sequence, protein_type, NUtility::random(this->config.protein_lifespan), thresholds, neighbours, generate_protein_parameters(Direction::number_of_directions, this->config.get_protein_stimuli(protein_type))));
				dna.rbegin()->set_protein_stimuli_level(this->config.get_protein_stimuli(protein_type));
				break;
			case ProteinType::regulatory:
				dna.push_back(Gene(sequence, protein_type, NUtility::random(this->config.protein_lifespan), thresholds, neighbours, generate_protein_parameters(this->config.number_of_hormones, this->config.get_protein_stimuli(protein_type))));
				dna.rbegin()->set_protein_stimuli_level(this->config.get_protein_stimuli(protein_type));
				break;
			case ProteinType::speciation:
				dna.push_back(Gene(sequence, protein_type, NUtility::random(this->config.protein_lifespan), thresholds, neighbours, generate_speciation_parameters(this->config.get_protein_stimuli(protein_type))));
				dna.rbegin()->set_protein_stimuli_level(this->config.get_protein_stimuli(protein_type));
				break;
			case ProteinType::transcribing:
				dna.push_back(Gene(sequence, protein_type, NUtility::random(this->config.protein_lifespan), thresholds, neighbours, generate_transcription_promoter(this->config.promoter_length)));
				dna.rbegin()->set_number_of_cell_types(this->config.number_of_cell_types);
				break;
		}
	}
	return dna;
}

vector<double> Nbryo::generate_protein_parameters(unsigned int n, const pair<double, double> *stimuli)
{
	double factor = stimuli->second - stimuli->first;
	vector<double> parameters (n);
	for (unsigned int p = 0; p < n; p++)
	{
		if (NUtility::random() < 0.5)
			parameters.push_back(0.0);
		else
			parameters.push_back(NUtility::random() * factor + stimuli->first);
	}
	return parameters;
}

vector<double> Nbryo::generate_speciation_parameters(const pair<double, double> *stimuli)
{
	vector<double> parameters (2);
	parameters.push_back(NUtility::random() * (stimuli->second - stimuli->first) + stimuli->first);
	parameters.push_back(NUtility::random(this->config.number_of_cell_types));
	return parameters;
}

boost::dynamic_bitset<> Nbryo::generate_transcription_promoter(unsigned int length)
{
	boost::dynamic_bitset<> promoter (length);
	for (unsigned int i = 0; i < this->config.promoter_length; i++)
		promoter[i] = NUtility::random() < 0.5;
	return promoter;
}
