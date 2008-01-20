#include "Cell.h"
#include "Protein.h"

bool Protein::is_active()
{
	// Check the concentrations of hormones
	for (int i = Hormone::a; i < Hormone::number_of_types; i++)
		if (this->host->get_hormone_concentration((Hormone::Type)i) < this->thresholds->at(i))
			return false;
	// Check the neighbourhood
	return true;
}
