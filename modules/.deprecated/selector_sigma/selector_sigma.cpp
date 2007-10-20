#include "selector_sigma.h"

using std::multiset;
using Sigma::random;

void initiate(const std::string &params)
{
	Sigma::roulette.reserve(atoi(params.c_str()));
}

void select(multiset<Specimen>::iterator &champ, multiset<Specimen> &candidates, int generation)
{
	double mean = 0.0;
	for (multiset<Specimen>::iterator i = candidates.begin(); i != candidates.end(); i++)
		mean += i->fitness;
	mean /= candidates.size();

	double sigma = 0.0;
	for (multiset<Specimen>::iterator i = candidates.begin(); i != candidates.end(); i++)
		sigma += pow(i->fitness - mean, 2.0);

	sigma = 2.0 * sqrt(sigma / (double)candidates.size());// * (double)generation;

	double winner_number = 0.0;
	for (multiset<Specimen>::iterator i = candidates.begin(); i != candidates.end(); i++)
	{
		winner_number += 1.0 + (i->fitness - mean) / sigma;
		Sigma::roulette.push_back(winner_number);
	}
	winner_number *= random();

	int slot = 0;
	champ = candidates.begin();
	while (Sigma::roulette[slot++] < winner_number)
		champ++;

	Sigma::roulette.clear();
}
