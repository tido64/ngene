/// Code based off Johan Høye's [HOYE2006]. Rewritten in C++ for Ngene with
/// modifications, hopefully making things simpler and faster.
///
/// Hormones is known as Chemicalconcentrations.java in HOYE2006. Some methods
/// were not implemented because they were thought of as redundant and not
/// useful.
/// - Normalizing no longer happens with each tick, but whenever a 
/// concentration is adjusted. This eliminates normalizing values that are
/// never touched, hopefully saving some CPU cycles.

#ifndef HORMONES
#define HORMONES

#include <algorithm>
#include <vector>

#include "HormoneType.h"

class Hormones
{
public:
	Hormones();

	/// Adjusts the concentration of a hormone.
	/// \param t The hormone to adjust
	/// \param n The amount to adjust by
	void adjust_concentration(Hormone::Type t, double n);

	/// Gets the current concentration of a hormone.
	double get_concentration(Hormone::Type t) const;

private:
	const double MAX_CONCENTRATION,		///< Maximum allowed concentration of a hormone
		MIN_CONCENTRATION;				///< Minimum allowed concentration of a hormone
	std::vector<double> concentrations;	///< Stores all hormone concentrations
};

#endif
