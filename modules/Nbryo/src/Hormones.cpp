#include "Hormones.h"

using std::max;
using std::min;

Hormones::Hormones()
: MAX_CONCENTRATION(1.0), MIN_CONCENTRATION(0.0), concentrations(Hormone::number_of_types, MIN_CONCENTRATION)
{ }

void Hormones::adjust_concentration(Hormone::Type t, double n)
{
	if (n > 0)
		this->concentrations[t] = min(this->concentrations[t] + n, this->MAX_CONCENTRATION);
	else
		this->concentrations[t] = max(this->concentrations[t] + n, this->MIN_CONCENTRATION);
}

double Hormones::get_concentration(Hormone::Type t) const
{
	return this->concentrations[t];
}
