/// Assesses the fitness of the organism.

#include "../../../src/Interfaces/Fitness.h"
#include "../../../src/Development/Cell.h"
#include <fstream>
#include <sstream>
#include <map>

namespace N
{
	Coordinates boundaries;
	std::map<Coordinates, int> target;
	std::string name;
}

using std::ifstream;
using std::getline;
using std::map;
using std::string;
using std::stringstream;

void assess(Specimen &individual)
{
	boost::any phenotype_container;
	Ngene::phenotype(phenotype_container, individual.genotype);
	map<Coordinates, Cell> specimen (*boost::unsafe_any_cast< map<Coordinates, Cell> >(&phenotype_container));

	int points = 0;
	Coordinates slot;
	map<Coordinates, int>::const_iterator t_result;
	map<Coordinates, Cell>::const_iterator s_result;
	for (int z = 0; z < N::boundaries.z; z++)
	{
		slot.z = z;
		for (int y = 0; y < N::boundaries.y; y++)
		{
			slot.y = y;
			for (int x = 0; x < N::boundaries.x; x++)
			{
				slot.x = x;
				s_result = specimen.find(slot);
				t_result = N::target.find(slot);

				if (s_result != specimen.end())
					if (t_result != N::target.end())
						points += (s_result->second.type == t_result->second) ? 2 : 1;
				else if (t_result == N::target.end())
					points += 2;
			}
		}
	}
	if (points == 0)
		individual.fitness = 0;
	else
		individual.fitness
			= static_cast<double>(points)
			/ static_cast<double>(N::boundaries.x * N::boundaries.y * N::boundaries.z * 2);
}

void initiate(const char *parameters)
{
	ifstream target_phenotype (parameters);
	if (target_phenotype.is_open())
	{
		N::name = "ArtDev3D.N fitness module (target=";
		N::name += parameters;
		N::name += ")";

		string tmp;
		getline(target_phenotype, tmp);
		N::boundaries.x = atoi(&tmp[6]);
		getline(target_phenotype, tmp);
		N::boundaries.y = atoi(&tmp[6]);
		getline(target_phenotype, tmp);
		N::boundaries.z = atoi(&tmp[6]);

		int x, y, z, t;
		while (!target_phenotype.eof())
		{
			target_phenotype >> x >> y >> z >> t;
			N::target[Coordinates(x, y, z)] = t;
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
	return N::name.c_str();
}
