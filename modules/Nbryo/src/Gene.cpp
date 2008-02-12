#include "Gene.h"

using std::pair;
using std::vector;

Gene::Gene(const Gene &gene)
: sequence(gene.sequence), protein_type(gene.protein_type), protein_lifespan(gene.protein_lifespan), protein_thresholds(gene.protein_thresholds), protein_neighbourhood(gene.protein_neighbourhood), number_of_cell_types(gene.number_of_cell_types), protein_stimuli(gene.protein_stimuli)
{
	if (gene.protein_promoter.size() > 0)
		this->protein_promoter = gene.protein_promoter;
	if (gene.protein_parameters.size() > 0)
		this->protein_parameters = gene.protein_parameters;
}

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
	switch (NUtility::random(Mutable::number_of_properties))
	{
		case Mutable::sequence: // mutate the dna sequence of this gene
			this->sequence[NUtility::random(this->protein_promoter.size())].flip();
			break;
		case Mutable::lifespan: // increase/decrease lifespan of proteins
			if (this->protein_lifespan == 0)
				this->protein_lifespan++;
			else
				NUtility::random() < 0.5 ? this->protein_lifespan++ : this->protein_lifespan--;
			break;
		case Mutable::thresholds: // mutates the hormonal thresholds in proteins
			if (!this->protein_thresholds.empty())
				this->protein_thresholds[NUtility::random(this->protein_thresholds.size())] += NUtility::random(-0.1, 0.1);
			break;
		case Mutable::neighbourhood:
			this->protein_neighbourhood[NUtility::random(Direction::number_of_directions)] = (CellType::Type)((int)NUtility::random(-1, CellType::number_of_types + 1));
			break;
		default:
			switch (this->protein_type)
			{
				case ProteinType::mitotic:
					if (!this->protein_parameters.empty())
						this->protein_parameters[NUtility::random(this->protein_parameters.size())]
							= (NUtility::random() < 0.5) ? 0.0 : NUtility::random(this->protein_stimuli.first, this->protein_stimuli.second);
					break;
				case ProteinType::regulatory:
					if (!this->protein_parameters.empty())
						this->protein_parameters[NUtility::random(this->protein_parameters.size())]
							= NUtility::random(this->protein_stimuli.first, this->protein_stimuli.second);
					break;
				case ProteinType::speciation:
					if (NUtility::random() > 0.5) // mutate stimulus level
						this->protein_parameters[0]
							= NUtility::random(this->protein_stimuli.first, this->protein_stimuli.second);
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

	if (!gene.protein_promoter.empty())
		this->protein_promoter = gene.protein_promoter;

	this->protein_thresholds = gene.protein_thresholds;
	this->protein_neighbourhood = gene.protein_neighbourhood;

	if (!gene.protein_parameters.empty())
		this->protein_parameters = gene.protein_parameters;

	this->number_of_cell_types = gene.number_of_cell_types;
	this->protein_stimuli = gene.protein_stimuli;
}
