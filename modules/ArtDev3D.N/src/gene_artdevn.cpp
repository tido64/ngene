#include "gene_artdevn.h"

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
}

void phenotype(boost::any &phenotype, const Genotype &genotype)
{
	N::artdev3d.evolve(genotype);
	phenotype = N::artdev3d.get_organism()->cells;
}

void seed(vector<boost::any> &genotype)
{
	for (unsigned int i = 0; i < N::setup.genes_number ; i++)
		genotype.push_back(Gene (&N::setup));
}

const char *species()
{
	return N::name.c_str();
}

const char *str(const Genotype &genotype)
{
	N::artdev3d.evolve(genotype);

	Organism *o (N::artdev3d.get_organism());
	stringstream ss;
	for (map<Coordinates, Cell>::const_iterator i = o->cells.begin(); i != o->cells.end(); i++)
		ss << i->first.x << " " << i->first.y << " " << i->first.z << " " << i->second.type << "\n";
	N::name = ss.str();

	return N::name.c_str();
}
