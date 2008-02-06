#include "Ribosome.h"

using std::vector;

void Ribosome::translate(const Gene *gene)
{
	Protein polypeptide (gene);
	polypeptide.make_aware(this->host);
	this->host->proteins.push_back(polypeptide);
}
