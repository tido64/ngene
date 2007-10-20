#include "selector_fitness_proportionate.h"

using std::multiset;
using FitnessProportionate::random;

void initiate(const std::string &params)
{
	FitnessProportionate::roulette.reserve(atoi(params.c_str()));
}

void select(multiset<Specimen>::iterator &champ, multiset<Specimen> &candidates, int generation)
{
	double winner = 0.0;
	for (multiset<Specimen>::iterator i = candidates.begin(); i != candidates.end(); i++)
	{
		winner += i->fitness;
		FitnessProportionate::roulette.push_back(winner);
	}
	winner *= random();

	int slot = 0;
	champ = candidates.begin();
	while (FitnessProportionate::roulette[slot++] < winner)
		champ++;

	FitnessProportionate::roulette.clear();
}
