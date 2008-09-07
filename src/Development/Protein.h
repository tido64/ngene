/// A generic protein commonly used in development systems.

#ifndef PROTEIN
#define PROTEIN

#include <vector>

struct Protein
{
	int
		life,					///< The life of the protein
		meta,					///< Metadata can hold system specific data
		type;					///< The type of the protein
	std::vector<int>
		neighbourhood_criteria;	///< An activation criteria based on the neighbouring cells' state
	std::vector<double>
		chemical_criteria,		///< An activation criteria based on the chemical levels in the cell
		parameters;				///< The parameters that can be applied on the cell
};

#endif
