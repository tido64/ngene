#include "../../../src/Interfaces/Fitness.h"
#include <fstream>
#include <map>
#include <vector>
#include "../../../src/Development/Cell.h"
#include "../../../src/Development/Coordinates.h"

namespace cgp
{
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
		//printf("==>");
		slot.x = -cgp::offset.x;
		slot.y = y - cgp::offset.y;
		for (unsigned int x = 0; x < cgp::target.size(); x++)
		{
			s_result = specimen.find(slot);
			if (s_result != specimen.end())
			{
				if (cgp::target[x][y] > 0)
					points += (static_cast<unsigned int>(s_result->second.type) == cgp::target[x][y]) ? 2 : 1;
				//printf("  [%d,%d] %d/%u", slot.x, slot.y, s_result->second.type, cgp::target[x][y]);
			}
			else
			{
				if (cgp::target[x][y] < 1)
					points += 2;
				//printf("  [%d,%d] -/%u", slot.x, slot.y, cgp::target[x][y]);
			}
			slot.x++;
		}
		//printf("\n");
	}

	individual.fitness = points / cgp::baseline;
}

void initiate(const char *parameters)
{
	std::vector<std::string> tmp;
	std::ifstream target (parameters);
	if (!target.is_open())
	{
		printf("==> Failed to open target phenotype: %s\n", parameters);
		printf("==> Falling back to: French Flag\n");

		// 00 = empty, 01 = blue, 10 = red, 11 = white
		tmp.push_back("111333222");
		tmp.push_back("111333222");
		tmp.push_back("111333222");
		tmp.push_back("111333222");
	}
	else
	{
		do
		{
			tmp.push_back("");
		} while (getline(target, tmp.back()));
	}

	char c;
	cgp::target.reserve(tmp.front().size());
	for (unsigned int x = 0; x < tmp.front().size(); x++)
	{
		cgp::target.push_back(std::vector<unsigned int> ());
		cgp::target.back().reserve(tmp.size());
		for (unsigned int y = 0; y < tmp.size(); y++)
		{
			c = tmp[y][x];
			cgp::target[x].push_back(atoi(&c));
		}
	}
	cgp::baseline = cgp::target.size() * cgp::target.front().size() * 2;
	cgp::offset.x = cgp::target.size() / 2;
	cgp::offset.y = cgp::target.front().size() / 2;
}

const char *name()
{
	return cgp::name.c_str();
}
