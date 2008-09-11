/// The generic development framework that any system has to extend. Contains
/// all the necessary entry points for Ngene.

#include "../Interfaces/Genotype.h"
#include "Organism.h"

class AbstractDevelopment
{
protected:
	const unsigned int ticks;	///< Number of ticks the development should run
	Organism *organism;			///< The organism to be/already developed

	AbstractDevelopment(int t) : ticks(t) { }

	~AbstractDevelopment()
	{
		delete this->organism;
	}

public:

	/// Evolves or develops the organism given a genotype.
	void evolve(const Genotype &g)
	{
		if (this->organism != 0)
			delete this->organism;
		this->organism = new Organism(g);
		initialize();
		for (unsigned int i = 0; i < ticks; i++)
			execute();
	}

	/// The program that is run with each tick. Must be implemented.
	virtual void execute() = 0;

	/// Returns the organism that is currently held in the system.
	Organism *get_organism()
	{
		return this->organism;
	}

	/// System dependent initialization of the organism to develop. Must be
	/// implemented.
	virtual void initialize() = 0;
};
