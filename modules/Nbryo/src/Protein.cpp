#include "Cell.h"
#include "Protein.h"

using std::vector;

bool Protein::is_active()
{
	// Check the concentrations of hormones
	for (int i = Hormone::a; i < Hormone::number_of_types; i++)
		if (this->host->get_hormone_concentration((Hormone::Type)i) < this->thresholds[i])
			return false;

	// Check the neighbourhood
	vector<CellType::Type> current_neighbours;
	this->host->get_neighbours(current_neighbours);
	for (unsigned int i = 0; i < current_neighbours.size(); i++)
		if (this->neighbours[i] != CellType::number_of_types && current_neighbours[i] != this->neighbours[i])
			return false;

	return true;
}
