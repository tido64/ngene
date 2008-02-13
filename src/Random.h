/// This is the Mersenne Twister random number generator.

#ifndef RANDOM_GENERATOR
#define RANDOM_GENERATOR

#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_real.hpp>
#include <boost/random/variate_generator.hpp>

class Random
{
public:
	Random();

	/// Returns the next random real number.
	double next();

	/// Returns the next random real number within [min, max).
	double next(double min, double max);

	/// Returns the next random integer within [0, i).
	int next_int(int i);

	/// Returns the next random integer within [min, max).
	int next_int(int min, int max);

private:
	boost::mt19937 rand_gen;
	boost::uniform_real<double> rand_dist;
	boost::variate_generator<boost::mt19937 &, boost::uniform_real<double> > mt_rand;
};

#endif
