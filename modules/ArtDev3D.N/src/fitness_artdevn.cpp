/// Assesses the fitness of the organism.

#include "../../../src/Interfaces/Fitness.h"
#include "../../../src/Development/Cell.h"
#include <fstream>
#include <map>
#include <sstream>

namespace N
{
	double max_points;
	Coordinates offset;
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
	ngene::phenotype(phenotype_container, individual.genotype);
	map<Coordinates, Cell> specimen (*boost::unsafe_any_cast< map<Coordinates, Cell> >(&phenotype_container));

	//for (map<Coordinates, Cell>::iterator i = specimen.begin(); i != specimen.end(); i++)
	//	printf("[%d,%d,%d] = %d\n", i->first.x, i->first.y, i->first.z, i->second.type);
	//exit(0);

	int points = 0;
	Coordinates slot;
	map<Coordinates, int>::const_iterator t_result;
	map<Coordinates, Cell>::const_iterator s_result;
	for (int z = -N::offset.z; z <= N::offset.z; z++)
	{
		slot.z = z;
		for (int y = -N::offset.y; y <= N::offset.y; y++)
		{
			slot.y = y;
			for (int x = -N::offset.x; x <= N::offset.x; x++)
			{
				slot.x = x;
				s_result = specimen.find(slot);
				t_result = N::target.find(slot);

				if (s_result != specimen.end())
				{
					if (t_result != N::target.end())
						points += (s_result->second.type == t_result->second) ? 2 : 1;
				}
				else
				{
					if (t_result == N::target.end())
						points += 2;
				}
			}
		}
	}
	individual.fitness = points / N::max_points;
}

void initiate(const char *parameters)
{
	ifstream target_phenotype (parameters);
	if (!target_phenotype.is_open())
	{
		printf("==> Failed to open target phenotype: %s\n", parameters);
		exit(-1);
	}

	N::name = "ArtDev3D.N fitness module (target=";
	N::name += parameters;
	N::name += ")";

	string tmp;
	getline(target_phenotype, tmp);
	N::offset.x = atoi(&tmp[6]);
	getline(target_phenotype, tmp);
	N::offset.y = atoi(&tmp[6]);
	getline(target_phenotype, tmp);
	N::offset.z = atoi(&tmp[6]);

	N::max_points = N::offset.x * N::offset.y * N::offset.z * 2;
	N::offset.x >>= 1;
	N::offset.y >>= 1;
	N::offset.z >>= 1;

	int x, y, z, t;
	while (!target_phenotype.eof())
	{
		target_phenotype >> x >> y >> z >> t;
		N::target[Coordinates(x - N::offset.x, y - N::offset.y, z - N::offset.z)] = t;
	}
	target_phenotype.close();
}

const char *name()
{
	return N::name.c_str();
}
