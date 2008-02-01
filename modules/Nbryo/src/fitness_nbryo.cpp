/// Assesses the fitness of the organism.

#include "../../../src/Interfaces/Fitness.h"
#include <fstream>
#include <sstream>
#include <map>

#include "CellType.h"
#include "Coordinates.h"

namespace Nbryo
{
	Coordinates boundaries;
	std::map<Coordinates, CellType::Type> target;
	unsigned int development_time;
	std::string name;
}

using std::ifstream;
using std::getline;
using std::map;
using std::string;
using std::stringstream;

void assess(Specimen &individual)
{
	map<Coordinates, CellType::Type> phenotype;

	int points = 0;
	for (int z = 0; z < Nbryo::boundaries.z; z++)
	{
		static Coordinates check;
		check.z = z;
		for (int y = 0; y < Nbryo::boundaries.y; y++)
		{
			check.y = y;
			for (int x = 0; x < Nbryo::boundaries.x; x++)
			{
				static map<Coordinates, CellType::Type>::const_iterator a, b;

				check.x = x;
				a = phenotype.find(check);
				b = Nbryo::target.find(check);

				if (a != phenotype.end() && b != Nbryo::target.end())
					points += a->second == b->second ? 2 : 1;
			}
		}
	}
	individual.fitness = (double)points / (double)(Nbryo::boundaries.x * Nbryo::boundaries.y * Nbryo::boundaries.z * 2);
}

void initiate(const string &parameters)
{
	stringstream config (parameters);
	config >> Nbryo::name >> Nbryo::development_time >> Nbryo::boundaries.x >> Nbryo::boundaries.y >> Nbryo::boundaries.z;

	ifstream target_phenotype (Nbryo::name.c_str());
	if (target_phenotype.is_open())
	{
		config.clear();
		config << "Nbryo fitness module (target = " << Nbryo::name << ", development time = " << Nbryo::development_time << ")";
		Nbryo::name = config.str();

		string tmp;
		getline(target_phenotype, tmp);
		getline(target_phenotype, tmp);
		getline(target_phenotype, tmp);

		while (!target_phenotype.eof())
		{
			int x, y, z, t;
			target_phenotype >> x >> y >> z >> t;
			Nbryo::target[Coordinates(x, y, z)] = (CellType::Type)t;
		}
		target_phenotype.close();
	}
}

const char *name()
{
	return Nbryo::name.c_str();
}
