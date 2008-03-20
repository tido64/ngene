/// Assesses the fitness of the organism.

#include "../../../src/Interfaces/Fitness.h"
#include <fstream>
#include <sstream>
#include <map>

#include "CellType.h"
#include "Coordinates.h"

typedef std::map<Coordinates, CellType::Type> CellMap;

namespace Nbryo
{
	Coordinates boundaries;
	CellMap target;
	std::string name;
}

using std::ifstream;
using std::getline;
using std::string;
using std::stringstream;

void assess(Specimen &individual)
{
	boost::any phenotype_container;
	Ngene::phenotype(phenotype_container, individual.genotype);
	CellMap phenotype (*boost::unsafe_any_cast<CellMap>(&phenotype_container));

	Coordinates check;
	CellMap::const_iterator a, b;

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
				a = phenotype.find(check);
				b = Nbryo::target.find(check);

				if (a != phenotype.end() && b != Nbryo::target.end())
					points += (a->second == b->second) ? 2 : 1;
				else if (a == phenotype.end() && b == Nbryo::target.end())
					points += 2;
			}
		}
	}
	individual.fitness = (points <= 0) ? 0 : static_cast<double>(points) / static_cast<double>(Nbryo::boundaries.x * Nbryo::boundaries.y * Nbryo::boundaries.z * 2);
}

void initiate(const char *parameters)
{
	ifstream target_phenotype (parameters);
	if (target_phenotype.is_open())
	{
		Nbryo::name = "Nbryo fitness module (target=";
		Nbryo::name += parameters;
		Nbryo::name += ")";

		string tmp;
		getline(target_phenotype, tmp);
		Nbryo::boundaries.x = atoi(&tmp[6]);
		getline(target_phenotype, tmp);
		Nbryo::boundaries.y = atoi(&tmp[6]);
		getline(target_phenotype, tmp);
		Nbryo::boundaries.z = atoi(&tmp[6]);

		int x, y, z, t;
		while (!target_phenotype.eof())
		{
			target_phenotype >> x >> y >> z >> t;
			Nbryo::target[Coordinates(x, y, z)] = static_cast<CellType::Type>(t);
		}
		target_phenotype.close();
	}
	else
	{
		printf("  * Failed to open target phenotype: %s\n", parameters);
		exit(-1);
	}
}

const char *name()
{
	return Nbryo::name.c_str();
}
