#ifndef PLOTTER_INTERFACE
#define PLOTTER_INTERFACE

#include <vector>

class IPlotter
{
public:
	virtual bool is_initiated() = 0;
	virtual void plot(const int generation, double min, double avg, double max) = 0;
};

#endif
