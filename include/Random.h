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
/// 	inline unsigned int next_int(unsigned int i);
/// 	inline int next_int(int min, int max);
/// 	inline unsigned int operator ()(unsigned int i);
/// 	void seed(unsigned int s);
/// 	void seed(unsigned int seed[], unsigned int seedc);
/// 
/// private:
/// 	Random();
//};

#ifndef RANDOM_H_
#define RANDOM_H_

#include "Mersenne_twister.h"

#endif
