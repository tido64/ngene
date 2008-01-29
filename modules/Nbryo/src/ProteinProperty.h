/// Code based off Johan Høye's [HOYE2006]. Rewritten in C++ for Ngene with
/// modifications, hopefully making things simpler and faster.

#ifndef PROTEINPROPERTY
#define PROTEINPROPERTY

namespace ProteinProperty
{
	enum Property
	{
		lifespan,
		promoter,
		thresholds,
		neighbours,
		parameters,
		number_of_properties
	};
}

#endif
