#include "Ribosome.h"

using std::vector;

ProteinMolecule *Ribosome::translate(vector<Gene>::const_iterator gene)
{
	ProteinMolecule *polypeptide;
	switch (gene->protein_type)
	{
		case ProteinType::adjusting:
			polypeptide = new Protein_Adjusting(&gene->protein_thresholds, gene->protein_lifespan, &gene->parameters);
			break;
		case ProteinType::division:
			polypeptide = new Protein_Division(&gene->protein_thresholds, gene->protein_lifespan, &gene->parameters);
			break;
		case ProteinType::speciation:
			polypeptide = new Protein_Speciation(&gene->protein_thresholds, gene->protein_lifespan, &gene->parameters);
			break;
		case ProteinType::transcribing:
			polypeptide = new Protein_Transcribing(&gene->protein_thresholds, gene->protein_lifespan, &gene->parameters);
			break;
	}
	return polypeptide;
}
