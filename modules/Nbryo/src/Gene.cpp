#include "Gene.h"

using std::string;
using std::vector;

Gene::Gene(const ProteinType::Type pt, const int pt_lifespan, const vector<double> pt_thresholds,
		   const string s, const vector<double> &p)
	: protein_type(pt), protein_lifespan(pt_lifespan), protein_thresholds(pt_thresholds), sequence(s), parameters(p)
{
}
