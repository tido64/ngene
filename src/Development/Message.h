/// A common message used to exchange information between cells.

#ifndef MESSAGE
#define MESSAGE

#include "Cell.h"

namespace From
{
	enum Type
	{
		above,
		above_left,
		above_right,
		left,
		right,
		below,
		below_left,
		below_right,
		front,
		back
	};
}

struct Message
{
	int type;						///< The sender's type
	std::vector<double> chemicals;	///< The sender's chemicals levels
	Coordinates coords;				///< The sender of this message

	Message() :
		type(-1) { }

	Message(const Cell &c) :
		type(c.type),
		chemicals(c.chemicals),
		coords(c.coords) { }
};

#endif
