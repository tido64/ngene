/*-- Boundaries are implemented in output-writer and not development module --*/

#include <Genotype.h>
#include <sstream>

#include "ArtDev3D.h"
#include "ConfigManager.h"

namespace N
{
	unsigned int ticks;
	std::string name;
	Coordinates boundaries;
	Setup setup;
	ArtDev3D *artdev3d;
}

using std::endl;
using std::map;
using std::stringstream;
using std::vector;

void initiate(const char *parameters)
{
	stringstream in (parameters);
	in >> N::ticks >> N::boundaries.x >> N::boundaries.y >> N::boundaries.z;
	N::name = "ArtDev3D.N (development time=";
	N::name += parameters;
	N::name += ')';

	ConfigManager config_manager;
	N::setup = config_manager.get_setup();

	N::artdev3d = new ArtDev3D (N::ticks, N::setup.cell_types_number, N::setup.min_stimuli);
}

void phenotype(Any &phenotype, const Genotype &genotype)
{
	N::artdev3d->evolve(genotype);
	phenotype = N::artdev3d->get_organism();
}

void seed(Genotype &genotype)
{
	for (unsigned int i = 0; i < N::setup.genes_number ; i++)
		genotype.push_back(Gene (&N::setup, ngene::random));
}

const char *species()
{
	return N::name.c_str();
}

const char *str(const Genotype &genotype)
{
	stringstream ss;
	ss << "sizeX=" << N::boundaries.x << endl
		<< "sizeY=" << N::boundaries.y << endl
		<< "sizeZ=" << N::boundaries.z << endl;

	N::artdev3d->evolve(genotype);
	map<Coordinates, Cell> o (N::artdev3d->get_organism());
	delete N::artdev3d;

	Coordinates offset (N::boundaries.x >> 1, N::boundaries.y >> 1, N::boundaries.z >> 1);
	for (map<Coordinates, Cell>::iterator i = o.begin(); i != o.end(); i++)
	{
		Coordinates tmp (i->first.x + offset.x, i->first.y + offset.y, i->first.z + offset.z);

		if ((tmp.x >= 0) & (tmp.x < N::boundaries.x)
			& (tmp.y >= 0) & (tmp.y < N::boundaries.y)
			& (tmp.z >= 0) & (tmp.z < N::boundaries.z))
		{
			ss << tmp.x << " " << tmp.y << " " << tmp.z << " " << i->second.type << endl;
		}
	}
	N::name = ss.str();

	return N::name.c_str();
}
