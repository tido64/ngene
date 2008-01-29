#include "Ribosome.h"

using std::vector;

Protein *Ribosome::translate(const Gene *gene)
{
	Protein *polypeptide = new Protein(gene);
	polypeptide->make_aware(this->host);
	return polypeptide;
}
