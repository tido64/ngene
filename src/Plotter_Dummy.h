/// An implementation of IPlotter that outputs nothing.

#include "IPlotter.h"

class Plotter_Dummy : public IPlotter
{
public:
	Plotter_Dummy() { }
	~Plotter_Dummy() { }
	void plot(unsigned int generation, double min, double avg, double max) { }
};
