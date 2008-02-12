#include "Ribosome.h"

using std::vector;

Ribosome::Ribosome(Cell *host) : host(host)
{
	for (vector<Protein>::iterator i = this->host->proteins.begin(); i != this->host->proteins.end(); i++)
		i->make_aware(this->host);
}

void Ribosome::translate(const Gene *gene)
{
	Protein polypeptide (gene);
	polypeptide.make_aware(this->host);
	this->host->proteins.push_back(polypeptide);
}
