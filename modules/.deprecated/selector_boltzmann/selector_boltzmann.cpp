#include "selector_boltzmann.h"

using std::multiset;
using Boltzmann::random;

void initiate(const std::string &params)
{
	int size;
	std::istringstream parse (params);
	parse >> Boltzmann::T >> size;
	Boltzmann::roulette.reserve(size);

	std::ostringstream in_name;
	in_name << "Boltzmann Scaling (T=" << Boltzmann::T << ')';
	Boltzmann::name = in_name.str();
}

void select(multiset<Specimen>::iterator &champ, multiset<Specimen> &candidates, int generation)
{
	double g = 0.0;
	for (multiset<Specimen>::iterator i = candidates.begin(); i != candidates.end(); i++)
		g += i->fitness;
	g /= candidates.size();

	double s = 0.0;
	double winner_number = 0.0;
	for (multiset<Specimen>::iterator i = candidates.begin(); i != candidates.end(); i++)
	{
		s = exp(i->fitness / Boltzmann::T);
		winner_number += s / (s * g);
		Boltzmann::roulette.push_back(winner_number);
	}
	winner_number *= random();

	int slot = 0;
	champ = candidates.begin();
	while (Boltzmann::roulette[slot++] < winner_number)
		champ++;

	Boltzmann::roulette.clear();
}

const char *name()
{
	return Boltzmann::name.c_str();
}
