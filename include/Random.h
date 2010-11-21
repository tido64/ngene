/// Generic pseudo-random number generator. All generators must implement
/// the following interface. All numbers generated must be in the range of
/// [0, 1) unless specified otherwise.
///
/// class Random
/// {
/// public:
/// 	static Random *Instance()
/// 	{
/// 		static Random singleton;
/// 		return &singleton;
/// 	}
///
/// 	inline double next();
/// 	inline double next(double min, double max);
/// 	inline int next_int(int i);
/// 	inline int next_int(int min, int max);
///		inline double operator()()
/// 	inline int operator ()(int i);
/// 	void seed(unsigned int s);
/// 	void seed(unsigned int seed[], unsigned int seedc);
///
/// private:
/// 	Random();
/// };
///
/// Some benchmarks, compiled using -std=c++0x -O2 -ftree-vectorize -march=native:
///
/// 	C++0x:      Generated 2147483647 numbers in 16 secs
/// 	dSFMT:      Generated 2147483647 numbers in 15 secs
/// 	dSFMT SSE2: Generated 2147483647 numbers in  4 secs

#ifndef RANDOM_H_
#	define RANDOM_H_
#	if (1)  // dSFMT is faster with SSE2
#		include "Mersenne_twister.h"
#	else
#		include <random>

class Random
{
public:
	static Random *Instance()
	{
		static Random inst;
		return &inst;
	}

	inline double next()
	{
		return this->generator() / this->generator.max();
	}

	inline double next(double min, double max)
	{
		return this->next() * (max - min) + min;
	}

	inline int next_int(int i)
	{
		return static_cast<int>(this->next() * i);
	}

	inline int next_int(int min, int max)
	{
		return static_cast<int>(this->next() * (max - min)) + min;
	}

	inline double operator()()
	{
		return this->next();
	}

	inline int operator ()(int i)
	{
		return static_cast<int>(this->next() * i);
	}

private:
	std::mt19937 generator;

	Random() { }
	Random(const Random &);
	Random& operator=(const Random &);
};

#	endif
#endif
