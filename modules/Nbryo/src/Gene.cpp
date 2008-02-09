#include "Direction.h"
#include "Gene.h"

using std::pair;
using std::vector;

Gene::Gene(const Gene &gene)
: sequence(gene.sequence), protein_type(gene.protein_type), protein_lifespan(gene.protein_lifespan), protein_promoter(gene.protein_promoter), protein_thresholds(gene.protein_thresholds), protein_neighbourhood(gene.protein_neighbourhood), protein_parameters(gene.protein_parameters), number_of_cell_types(gene.number_of_cell_types), protein_stimuli(gene.protein_stimuli)
{ }

Gene::Gene(
	const boost::dynamic_bitset<> &sequence,
	const ProteinType::Type protein_type,
	const unsigned int protein_lifespan,
	const std::vector<double> &protein_thresholds,
	const std::vector<CellType::Type> &protein_neighbourhood,
	const boost::dynamic_bitset<> &protein_promoter)
: sequence(sequence), protein_type(protein_type), protein_lifespan(protein_lifespan), protein_promoter(protein_promoter), protein_thresholds(protein_thresholds), protein_neighbourhood(protein_neighbourhood)
{ }

Gene::Gene(
	const boost::dynamic_bitset<> &sequence,
	const ProteinType::Type protein_type,
	const unsigned int protein_lifespan,
	const std::vector<double> &protein_thresholds,
	const std::vector<CellType::Type> &protein_neighbourhood,
	const std::vector<double> &protein_parameters)
: sequence(sequence), protein_type(protein_type), protein_lifespan(protein_lifespan), protein_thresholds(protein_thresholds), protein_neighbourhood(protein_neighbourhood), protein_parameters(protein_parameters)
{ }


const boost::dynamic_bitset<> *Gene::get_sequence() const
{
	return &this->sequence;
}

void Gene::mutate()
{
	// Enter switch of DOOM!
	switch (NUtility::random(ProteinProperty::number_of_properties))
	{
		case ProteinProperty::lifespan: // increase/decrease lifespan of proteins
			if (this->protein_lifespan == 0)
				this->protein_lifespan++;
			else
				this->protein_lifespan += NUtility::random() < 0.5 ? 1 : -1;
			break;
		case ProteinProperty::thresholds: // mutates the hormonal thresholds in proteins
			if (!this->protein_thresholds.empty())
				this->protein_thresholds[NUtility::random(this->protein_thresholds.size())] += NUtility::random() * 0.2 - 0.1;
			break;
		case ProteinProperty::neighbourhood:
			this->protein_neighbourhood[NUtility::random(Direction::number_of_directions)] = (CellType::Type)((int)NUtility::random(CellType::number_of_types + 2) - 1);
			break;
		default:
			switch (this->protein_type)
			{
				case ProteinType::mitotic:
				case ProteinType::regulatory:
					if (!this->protein_parameters.empty())
						this->protein_parameters[NUtility::random(this->protein_parameters.size())]
							= NUtility::random() * (this->protein_stimuli.second - this->protein_stimuli.first) + this->protein_stimuli.first;
					break;
				case ProteinType::speciation:
					if (NUtility::random() > 0.5) // mutate stimulus level
						this->protein_parameters[0]
							= NUtility::random() * (this->protein_stimuli.second - this->protein_stimuli.first) + this->protein_stimuli.first;
					else // mutate cell type
						this->protein_parameters[1] = NUtility::random(this->number_of_cell_types);
					break;
				case ProteinType::transcribing: // flip a random bit in the promoter
					this->protein_promoter[NUtility::random(this->protein_promoter.size())].flip();
					break;
				default:
					throw "Gene::mutate: This should never happen.";
			}
			break;
	}
}

void Gene::set_number_of_cell_types(unsigned int n)
{
	this->number_of_cell_types = n;
}

void Gene::set_protein_stimuli_level(const pair<double, double> *s)
{
	this->protein_stimuli = *s;
}

void Gene::operator =(const Gene &gene)
{
	this->sequence = gene.sequence;
	this->protein_type = gene.protein_type;
	this->protein_lifespan = gene.protein_lifespan;
	this->protein_promoter = gene.protein_promoter;
	this->protein_thresholds = gene.protein_thresholds;
	this->protein_neighbourhood = gene.protein_neighbourhood;
	this->protein_parameters = gene.protein_parameters;
	this->number_of_cell_types = gene.number_of_cell_types;
	this->protein_stimuli = gene.protein_stimuli;
}
