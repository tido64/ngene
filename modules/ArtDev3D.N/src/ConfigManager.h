#if defined( WIN32) && defined(_DEBUG)
#pragma warning(disable: 4267)
#endif

/// This config class parses Johan's configuration files, and in time Nbryo's
/// own config format.

#include <cstdlib>
#include <fstream>
#include <string>
#include <utility>
#include <vector>

#include "ProteinType.h"
#include "Setup.h"

class ConfigManager
{
public:
	unsigned int
		gene_sequence_length,			///< The length of the gene sequence
		number_of_cell_types,			///< Number of different cell types to use
		number_of_dont_care_neighbours,	///< Number of initial don't-care-neighbours
		number_of_genes,				///< The size of the dna
		number_of_hormones,				///< Number of different hormone types to use
		promoter_length,				///< The length of the promoter used by the proteins
		protein_lifespan;				///< The maximum lifespan of a protein

	ConfigManager();
	const Setup get_setup() const;

private:
	std::vector<double> protein_weights;						///< ???
	std::vector<std::pair<double, double> > protein_stimuli;	///< Max (second) and min (first) stimuli a protein can change in a cell

	unsigned int parse_config(std::string &config, std::string str, unsigned int &index);
	void parse_protein_config(ProteinType::Type type, std::string &config, std::string str, unsigned int &index);
};
