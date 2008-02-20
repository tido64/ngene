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
	std::string name;
}

using std::ifstream;
using std::getline;
using std::map;
using std::string;
using std::stringstream;

void assess(Specimen &individual)
{
	const map<Coordinates, CellType::Type> *phenotype
		= (const map<Coordinates, CellType::Type> *)Ngene::phenotype(individual.genotype);

	Coordinates check;
	map<Coordinates, CellType::Type>::const_iterator a, b;

	int points = 0;
	for (int z = 0; z < Nbryo::boundaries.z; z++)
	{
		check.z = z;
		for (int y = 0; y < Nbryo::boundaries.y; y++)
		{
			check.y = y;
			for (int x = 0; x < Nbryo::boundaries.x; x++)
			{
				check.x = x;
				a = phenotype->find(check);
				b = Nbryo::target.find(check);

				/* For debugging purposes only
				printf("Comparing <%d, %d, %d>: ", check.x, check.y, check.z);
				a != phenotype->end() ? printf("%d ?= ", a->second) : printf("none ?= ");
				b != Nbryo::target.end() ? printf("%d\n", b->second) : printf("none\n");
				/*Bob*/

				if (a != phenotype->end() && b != Nbryo::target.end())
					points += (a->second == b->second) ? 2 : 1;
				else if (a == phenotype->end() && b == Nbryo::target.end())
					points += 2;
			}
		}
	}
	individual.fitness = points <= 0 ? 0 : static_cast<double>(points) / static_cast<double>(Nbryo::boundaries.x * Nbryo::boundaries.y * Nbryo::boundaries.z * 2);
	delete phenotype;
}

void initiate(const char *parameters)
{
	stringstream config (parameters);
	config >> Nbryo::name;

	ifstream target_phenotype (Nbryo::name.c_str());
	if (target_phenotype.is_open())
	{
		config.clear();
		config << "Nbryo fitness module (target=" << Nbryo::name << ")";
		Nbryo::name = config.str();

		string tmp;
		getline(target_phenotype, tmp);
		Nbryo::boundaries.x = atoi(&tmp[6]);
		getline(target_phenotype, tmp);
		Nbryo::boundaries.y = atoi(&tmp[6]);
		getline(target_phenotype, tmp);
		Nbryo::boundaries.z = atoi(&tmp[6]);

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
