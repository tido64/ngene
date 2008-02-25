#include "Random.h"

Random::Random()
: rand_dist(0, 1), mt_rand(rand_gen, rand_dist)
{ }

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
