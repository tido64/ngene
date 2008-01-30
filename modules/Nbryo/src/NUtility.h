/// A utility "box" containing random number generator and a string converter.

#ifndef NUTILITY
#define NUTILITY

#include <cstdlib>
#include <sstream>

namespace NUtility
{
	double random();

	unsigned int random(unsigned int k);

	template <class T>
	std::string to_string(const T &stringify)
	{
		std::stringstream ss;
		ss << stringify;
		return ss.str();
	}
}

#endif
