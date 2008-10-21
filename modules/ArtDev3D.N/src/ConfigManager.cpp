#include "ConfigManager.h"

using std::ifstream;
using std::istreambuf_iterator;
using std::make_pair;
using std::pair;
using std::string;
using std::vector;

ConfigManager::ConfigManager()
{
	ifstream config_file ("gp-config.properties");
	if (config_file.is_open())
	{
		unsigned int progress = 0;
		string config((istreambuf_iterator<char>(config_file)), istreambuf_iterator<char>());
		config_file >> config;
		config_file.close();

		this->number_of_genes = parse_config(config, "\ngp.genotype.dna.numberofgenes", progress);
		this->gene_sequence_length = parse_config(config, "gp.genotype.dna.gene.promotorlength", progress);

		this->protein_lifespan = parse_config(config, "gp.protein.maxtimetolive", progress);
		this->number_of_hormones = parse_config(config, "gp.protein.precondition.chemicaltype.no", progress);
		this->number_of_dont_care_neighbours = parse_config(config, "gp.protein.precondition.neighbour.dontcare.no", progress);

		this->promoter_length = parse_config(config, "gp.protein.subpromotorlength", progress);
		this->number_of_cell_types = parse_config(config, "gp.protein.celltype.no", progress);
	}
	else
	{
		printf("\nFailed to read general properties.\n");
		abort();
	}

	config_file.open("protein.properties");
	if (config_file.is_open())
	{
		unsigned int progress = 0;
		string config((istreambuf_iterator<char>(config_file)), istreambuf_iterator<char>());
		config_file >> config;
		config_file.close();
		this->protein_stimuli.assign(ProteinType::number_of_types, make_pair(0, 0));
		this->protein_weights.assign(ProteinType::number_of_types, 0);

		parse_protein_config(ProteinType::mitotic, config, "protein[0]", progress);
		parse_protein_config(ProteinType::metamorphic, config, "protein[1]", progress);
		parse_protein_config(ProteinType::regulatory, config, "protein[2]", progress);
		parse_protein_config(ProteinType::transcribing, config, "protein[3]", progress);
	}
	else
	{
		printf("\nFailed to read protein properties.\n");
		abort();
	}
}

const Setup ConfigManager::get_setup() const
{
	Setup setup;
	setup.cell_types_number = this->number_of_cell_types;
	setup.chemicals_number = this->number_of_hormones;
	setup.dont_care_neighbours = this->number_of_dont_care_neighbours;
	setup.gene_sequence_length = this->gene_sequence_length;
	setup.genes_number = this->number_of_genes;
	setup.max_protein_lifespan = this->protein_lifespan;
	setup.promoter_length = this->promoter_length;
	setup.max_stimuli = this->protein_stimuli[0].second;
	setup.min_stimuli = this->protein_stimuli[0].first;
	return setup;
}

unsigned int ConfigManager::parse_config(string &config, string str, unsigned int &index)
{
	index = config.find_first_of('=', config.find(str, index)) + 1;
	return atoi(config.substr(index, config.find_first_of('\n', index) - index).c_str());
}

void ConfigManager::parse_protein_config(ProteinType::Type type, string &config, string str, unsigned int &index)
{
	index = config.find(str + ".init.weight", index);
	if (config[index - 1] != '#')
	{
		index = config.find_first_of('=', index) + 1;
		this->protein_weights[type] = atof(
			config.substr(index, config.find_first_of('\n', index) - index).c_str());

		index = config.find(str + ".init.stimuli.min", index);
		if (config[index - 1] != '#')
		{
			index = config.find_first_of('=', index) + 1;
			this->protein_stimuli[type].first = atof(
				config.substr(index, config.find_first_of('\n', index) - index).c_str());
		}

		index = config.find(str + ".init.stimuli.max", index);
		if (config[index - 1] != '#')
		{
			index = config.find_first_of('=', index) + 1;
			this->protein_stimuli[type].second = atof(
				config.substr(index, config.find_first_of('\n', index) - index).c_str());
		}
	}
}
