#include "Ribosome.h"

using std::vector;

Protein *Ribosome::translate(vector<Gene>::const_iterator gene)
{
	Protein *polypeptide
		= new Protein(&gene->protein_thresholds, gene->protein_lifespan, &gene->parameters, gene->protein_type);
	polypeptide->make_aware(this->host);
	return polypeptide;
}
