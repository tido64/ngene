#include "Cell.h"
#include "Protein.h"

using std::vector;

Protein::Protein(const Gene *gene)
: type(gene->protein_type), lifespan(gene->protein_lifespan), thresholds(gene->protein_thresholds), neighbourhood(gene->protein_neighbourhood)
{
	if (!gene->protein_promoter.empty())
		this->promoter = gene->protein_promoter;
	if (!gene->protein_parameters.empty())
		this->parameters = gene->protein_parameters;
}

bool Protein::age()
{
	return this->lifespan-- == 0;
}

bool Protein::find_promoter(const boost::dynamic_bitset<> &sequence)
{
	bool found = false;
	for (unsigned int i = 0; i < sequence.size() - this->promoter.size(); i++)
	{
		if (sequence[i] == this->promoter[0])
		{
			found = true;
			for (unsigned int j = 1; j < this->promoter.size(); j++)
			{
				found &= (sequence[i + j] == this->promoter[j]);
				if (!found) break;
			}
			if (found) break;
		}
	}
	return found;
}

const vector<double> *Protein::get_parameters()
{
	return &this->parameters;
}

ProteinType::Type Protein::get_type()
{
	return this->type;
}

bool Protein::is_active()
{
	// Check the concentrations of hormones
	for (unsigned int i = Hormone::a; i < this->thresholds.size(); i++)
		if (this->host->get_hormones((Hormone::Type)i) > this->thresholds[i])
			return false;

	// Check the neighbourhood
	vector<CellType::Type> current_neighbourhood;
	this->host->get_neighbourhood(current_neighbourhood);
	for (unsigned int i = 0; i < current_neighbourhood.size(); i++)
		if (this->neighbourhood[i] != CellType::number_of_types && current_neighbourhood[i] != this->neighbourhood[i])
			return false;

	return true;
}

void Protein::make_aware(const Cell *host)
{
	this->host = host;
}

void Protein::operator =(const Protein &p)
{
	this->type = p.type;
	this->lifespan = p.lifespan;

	if (!p.promoter.empty())
		this->promoter = p.promoter;

	this->thresholds = p.thresholds;
	this->neighbourhood = p.neighbourhood;

	if (!p.parameters.empty())
		this->parameters = p.parameters;
}
