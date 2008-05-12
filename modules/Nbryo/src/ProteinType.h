/// Code based off Johan Høye's [HOYE2006]. Rewritten in C++ for Ngene with
/// modifications, hopefully making things simpler and faster.

#ifndef PROTEINTYPE
#define PROTEINTYPE

namespace ProteinType
{
	enum Type
	{
		mitotic,
		regulatory,
		speciation,
		transcribing,
		number_of_types
	};
}

#endif