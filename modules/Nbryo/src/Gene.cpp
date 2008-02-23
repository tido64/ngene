#include "Gene.h"

using std::pair;
using std::vector;

Gene::Gene(const Gene &gene)
: sequence(gene.sequence), protein_type(gene.protein_type), protein_lifespan(gene.protein_lifespan), protein_thresholds(gene.protein_thresholds), protein_neighbourhood(gene.protein_neighbourhood)
{
	if (!gene.protein_promoter.empty())
		this->protein_promoter = gene.protein_promoter;
	if (!gene.protein_parameters.empty())
		this->protein_parameters = gene.protein_parameters;
}

Gene::Gene(
	const boost::dynamic_bitset<> &s,
	const ProteinType::Type t,
	const unsigned int l,
	const vector<double> &th,
	const vector<CellType::Type> &n)
: sequence(s), protein_type(t), protein_lifespan(l), protein_thresholds(th), protein_neighbourhood(n)
{ }

void Gene::ergo_proxy(const boost::dynamic_bitset<> &p, const unsigned int n)
{
	this->protein_promoter = p;
	this->number_of_cell_types = n;
}

void Gene::ergo_proxy(const vector<double> &p, const pair<double, double> *s)
{
	this->protein_parameters = p;
	this->protein_stimuli = *s;
}

const boost::dynamic_bitset<> &Gene::get_sequence() const
{
	return this->sequence;
}

void Gene::mutate()
{
	// Enter switch of DOOM!
	switch (mt_rand.next_int(Mutable::number_of_properties))
	{
		case Mutable::sequence: // mutate the dna sequence of this gene
			this->sequence.flip(mt_rand.next_int(this->protein_promoter.size()));
			break;
		case Mutable::lifespan: // increase/decrease lifespan of proteins
			if (this->protein_lifespan == 0)
				this->protein_lifespan++;
			else
				(mt_rand.next() < 0.5) ? this->protein_lifespan++ : this->protein_lifespan--;
			break;
		case Mutable::thresholds: // mutates the hormonal thresholds in proteins
			if (!this->protein_thresholds.empty())
				this->protein_thresholds[mt_rand.next_int(this->protein_thresholds.size())] += mt_rand.next(-0.1, 0.1);
			break;
		case Mutable::neighbourhood:
			this->protein_neighbourhood[mt_rand.next_int(Direction::number_of_directions)] = static_cast<CellType::Type>(mt_rand.next_int(CellType::empty, CellType::number_of_types));
			break;
		default:
			switch (this->protein_type)
			{
				case ProteinType::mitotic:
					if (!this->protein_parameters.empty())
						this->protein_parameters[mt_rand.next_int(this->protein_parameters.size())]
							= (mt_rand.next() < 0.5) ? 0.0 : mt_rand.next(this->protein_stimuli.first, this->protein_stimuli.second);
					break;
				case ProteinType::regulatory:
					if (!this->protein_parameters.empty())
						this->protein_parameters[mt_rand.next_int(this->protein_parameters.size())]
							= mt_rand.next(this->protein_stimuli.first, this->protein_stimuli.second);
					break;
				case ProteinType::speciation:
					if (mt_rand.next() < 0.5) // mutate stimulus level
						this->protein_parameters[1]
							= mt_rand.next(this->protein_stimuli.first, this->protein_stimuli.second);
					else // mutate cell type
						this->protein_parameters[0] = mt_rand.next_int(this->number_of_cell_types);
					break;
				case ProteinType::transcribing: // flip a random bit in the promoter
					this->protein_promoter.flip(mt_rand.next_int(this->protein_promoter.size()));
					break;
				default:
					throw "Gene::mutate: This should never happen.";
			}
			break;
	}
}

Gene &Gene::operator =(const Gene &gene)
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

	return *this;
}
