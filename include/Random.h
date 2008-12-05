/// Generic random number generator interface. All generators must extend from
/// this interface. All numbers generated must be in the range of [0, 1)
/// unless specified otherwise.

#ifndef RANDOM_H_
#define RANDOM_H_

//#include "Mersenne_twister.h"

#include <ctime>
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_real.hpp>
#include <boost/random/variate_generator.hpp>

class Random
{
public:
	static Random *Instance()
	{
		static Random singleton;
		return &singleton;
	}

	/// Returns the next random real number.
	inline double next()
	{
		return this->mt_rand();
	}

	/// Returns the next random real number within [min, max).
	inline double next(double min, double max)
	{
		return this->mt_rand() * (max - min) + min;
	}

	/// Returns the next random integer within [0, i).
	inline unsigned int next_int(unsigned int i)
	{
		return static_cast<unsigned int>(this->mt_rand() * i);
	}

	/// Returns the next random integer within [min, max).
	inline int next_int(int min, int max)
	{
		return static_cast<int>(this->mt_rand() * (max - min)) + min;
	}

	/// Required by [lib.alg.random.shuffle]
	inline unsigned int operator ()(unsigned int i)
	{
		return static_cast<unsigned int>(this->mt_rand() * i);
	}

	void seed(unsigned int) { }
	void seed(unsigned int seed[], unsigned int seedc) { }

private:
	boost::mt19937 mersenne_twister;
	boost::uniform_real<double> uniform_real_dist;
	boost::variate_generator<boost::mt19937 &, boost::uniform_real<double> > mt_rand;

	Random() :
		mersenne_twister(static_cast<boost::uint32_t>(time(0))),
		uniform_real_dist(0, 1),
		mt_rand(mersenne_twister, uniform_real_dist) { }
};

#endif
