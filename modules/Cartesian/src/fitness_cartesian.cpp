#include "../../../src/Interfaces/Fitness.h"
#include <fstream>
#include <map>
#include <vector>
#include "../../../src/Development/Cell.h"
#include "../../../src/Development/Coordinates.h"

namespace cgp
{
	int width, height;
	double baseline;
	std::string name ("Cartesian");
	Coordinates offset;
	std::vector< std::vector<unsigned int> > target;
}

void assess(Specimen &individual)
{
	boost::any phenotype_container;
	ngene::phenotype(phenotype_container, individual.genotype);
	std::map<Coordinates, Cell> specimen (*boost::unsafe_any_cast< std::map<Coordinates, Cell> >(&phenotype_container));

	int points = 0;
	Coordinates slot;
	std::map<Coordinates, Cell>::const_iterator s_result;
	for (unsigned int y = 0; y < cgp::target.front().size(); y++)
	{
		slot.y = y + cgp::offset.y;
		slot.x = cgp::offset.x;
		for (unsigned int x = 0; x < cgp::target.size(); x++)
		{
			s_result = specimen.find(slot);
			if (s_result != specimen.end())
			{
				if (cgp::target[x][y] != 0)
					points += (static_cast<unsigned int>(s_result->second.type) == cgp::target[x][y]) ? 2 : 1;
			}
			else
			{
				if (cgp::target[x][y] == 0)
					points += 2;
			}
			slot.x++;
		}
	}
	individual.fitness = points;
}

void initiate(const char *parameters)
{
	std::ifstream target (parameters);
	if (!target.is_open())
	{
		printf("==> Failed to open target phenotype: %s\n", parameters);
		exit(-1);
	}

	std::vector<std::string> tmp;
	do
	{
		tmp.push_back("");
	} while (std::getline(target, tmp.back()));

	cgp::target.resize(tmp.front().size());
	for (unsigned int x = 0; x < tmp.front().size(); x++)
	{
		cgp::target.push_back(std::vector<unsigned int> (tmp.size()));
		for (unsigned int y = 0; y < tmp.size(); y++)
			cgp::target[x].push_back(tmp[x][y]);
	}
	cgp::offset.x = cgp::target.size() / 2;
	cgp::offset.y = cgp::target.front().size() / 2;
}

const char *name()
{
	return cgp::name.c_str();
}
