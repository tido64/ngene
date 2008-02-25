#include "Hormones.h"

using std::max;
using std::min;

const double
	Hormones::MAX_CONCENTRATION (1.0),
	Hormones::MIN_CONCENTRATION (0.0);

Hormones::Hormones()
: concentrations(Hormone::number_of_types, MIN_CONCENTRATION)
{ }

void Hormones::adjust_concentration(Hormone::Type t, double n)
{
	if (n > 0)
		this->concentrations[t] = min(this->concentrations[t] + n, MAX_CONCENTRATION);
	else
		this->concentrations[t] = max(this->concentrations[t] + n, MIN_CONCENTRATION);
}

double Hormones::get_concentration(Hormone::Type t) const
{
	return this->concentrations[t];
}
