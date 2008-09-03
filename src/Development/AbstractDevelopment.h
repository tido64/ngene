#include "../Interfaces/Genotype.h"
#include "Organism.h"

class AbstractDevelopment
{
protected:
	unsigned int ticks;
	Organism *organism;

	AbstractDevelopment(int t) : ticks(t) { }

	~AbstractDevelopment()
	{
		delete this->organism;
	}

public:
	void evolve(const Genotype &g)
	{
		if (this->organism != 0)
			delete this->organism;
		this->organism = new Organism(g);
		for (unsigned int i = 0; i < ticks; i++)
			execute();
	}

	virtual void execute() = 0;
};
