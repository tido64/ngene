#include "Random.h"

Random::Random()
//: mersenne_twister(time(0)), mt_rand(mersenne_twister)
: mersenne_twister(time(0)), uniform_real_dist(0, 1), mt_rand(mersenne_twister, uniform_real_dist)
{ }

Random &Random::Instance()
{
	static Random singleton;
	return singleton;
}

double Random::next()
{
	return this->mt_rand();
}

double Random::next(double min, double max)
{
	return this->mt_rand() * (max - min) + min;
}

unsigned int Random::next_int(unsigned int i)
{
	return static_cast<unsigned int>(this->mt_rand() * i);
}

int Random::next_int(int min, int max)
{
	return static_cast<int>(this->mt_rand() * (max - min)) + min;
}

int Random::operator ()(int i)
{
	return static_cast<int>(this->mt_rand() * i);
}
