#include "Ribosome.h"

using std::vector;

Protein *Ribosome::translate(vector<Gene>::const_iterator gene)
{
	Protein *polypeptide;
	switch (gene->get_protein_type())
	{
		case ProteinType::transcribing:
			polypeptide = new Protein(gene->get_protein_type(), gene->get_protein_lifespan(), gene->get_protein_thresholds(), gene->get_protein_promoter());
			break;
		default:
			polypeptide = new Protein(gene->get_protein_type(), gene->get_protein_lifespan(), gene->get_protein_thresholds(), gene->get_protein_parameters());
			break;
	}
	polypeptide->make_aware(this->host);
	return polypeptide;
}
