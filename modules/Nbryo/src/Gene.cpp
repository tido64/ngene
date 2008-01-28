#include "Gene.h"

using std::vector;

unsigned int Gene::get_protein_lifespan() const
{
	return this->protein_lifespan;
}

const vector<double> *Gene::get_protein_parameters() const
{
	return &this->protein_parameters;
}

const boost::dynamic_bitset<> *Gene::get_protein_promoter() const
{
	return &this->protein_promoter;
}

ProteinType::Type Gene::get_protein_type() const
{
	return this->protein_type;
}

const boost::dynamic_bitset<> *Gene::get_sequence() const
{
	return &this->sequence;
}

const vector<double> *Gene::get_protein_thresholds() const
{
	return &this->protein_thresholds;
}

void Gene::operator=(const Gene &gene)
{
	this->sequence = *gene.get_sequence();
	this->protein_type = gene.get_protein_type();
	this->protein_lifespan = gene.get_protein_lifespan();
	this->protein_promoter = *gene.get_protein_promoter();
	this->protein_thresholds = *gene.get_protein_thresholds();
	this->protein_parameters = *gene.get_protein_parameters();
}
