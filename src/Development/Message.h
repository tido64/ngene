/// A common message used to exchange information between cells.

#ifndef MESSAGE
#define MESSAGE

#include <vector>
#include "Coordinates.h"

struct Message
{
	int type;						///< The sender's type
	std::vector<double> chemicals;	///< The sender's chemicals levels
	Coordinates coords;				///< The sender of this message

	Message() :
		type(-1) { }

	Message(const int t, const std::vector<double> &ch, const Coordinates &co) :
		type(t),
		chemicals(ch),
		coords(co) { }
};

#endif
