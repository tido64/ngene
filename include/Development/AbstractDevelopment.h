/// The generic development framework that any system has to extend. Contains
/// all the necessary entry points for Ngene.

#include "Organism.h"

class AbstractDevelopment
{
private:
	Organism *organism;							///< The organism to be/already developed
	std::map<Coordinates, Cell> cell_buffer;	///< New cells are stored in a buffer before "written"

	/// Exchange information between all cells. Called internally.
	void exchange()
	{
		Message empty;
		std::vector<std::map<Coordinates, Cell>::const_iterator> neighbours;
		for (std::map<Coordinates, Cell>::iterator i = this->organism->cells.begin(); i != this->organism->cells.end(); i++)
		{
			i->second.messages.clear();
			neighbours.clear();
			neighbours.push_back(this->organism->cells.find(i->first.above()));
			neighbours.push_back(this->organism->cells.find(i->first.above_left()));
			neighbours.push_back(this->organism->cells.find(i->first.above_right()));
			neighbours.push_back(this->organism->cells.find(i->first.left()));
			neighbours.push_back(this->organism->cells.find(i->first.right()));
			neighbours.push_back(this->organism->cells.find(i->first.below()));
			neighbours.push_back(this->organism->cells.find(i->first.below_left()));
			neighbours.push_back(this->organism->cells.find(i->first.below_right()));
			neighbours.push_back(this->organism->cells.find(i->first.front()));
			neighbours.push_back(this->organism->cells.find(i->first.back()));

			for (std::vector<std::map<Coordinates, Cell>::const_iterator>::iterator c = neighbours.begin(); c != neighbours.end(); c++)
			{
				if (*c == this->organism->cells.end())
					i->second.messages.push_back(empty);
				else
					i->second.messages.push_back(Message ((*c)->second.type, (*c)->second.chemicals, (*c)->second.coords));
			}
		}
	}

	/// Adds the new cells to the organism. Called internally.
	void flush()
	{
		if (!this->cell_buffer.empty())
		{
			this->organism->cells.insert(this->cell_buffer.begin(), this->cell_buffer.end());
			this->cell_buffer.clear();
		}
	}

protected:
	const unsigned int ticks;	///< Number of ticks the development should run

	AbstractDevelopment(int t) : organism(0), ticks(t) { }

	~AbstractDevelopment()
	{
		delete this->organism;
	}

	/// Performs cell division into given direction (location). These cells are
	/// not immediately added to the organism but stored in a buffer and added
	/// before the end of a tick.
	/// \param c The cell to divide
	/// \param l The location to place the new cell
	Cell &divide_cell(const Cell &c, const Coordinates &l)
	{
		this->cell_buffer[l] = Cell (c, l);
		return this->cell_buffer[l];
	}

	/// The cell program that is run at each tick. Must be implemented.
	virtual void execute(Cell &) = 0;

	/// Checks whether or not there exists a cell in the given coordinates.
	/// \param l The location to look for a cell
	bool exists(const Coordinates &l)
	{
		return this->organism->cells.find(l) != this->organism->cells.end();
	}

	/// System dependent initialization of the organism to develop. Genotypes
	/// should be casted into its appropriate data type and initial cells
	/// created and injected into the empty organism. Must be
	/// implemented.
	virtual void initialize(Organism *) = 0;

	/// Checks for a new cell in the given location but not yet "written" to
	/// the organism.
	bool queued(const Coordinates &l)
	{
		return this->cell_buffer.find(l) != this->cell_buffer.end();
	}

	void remove(const Coordinates &l)
	{
		//this->organism->cells.erase(l);
	}

public:
	/// Evolves or develops the organism given a genotype.
	void evolve(const Genotype &g)
	{
		if (this->organism != 0)
			delete this->organism;
		this->organism = new Organism(g);
		initialize(this->organism);
		for (unsigned int i = 0; i < ticks; i++)
		{
			exchange();
			for (std::map<Coordinates, Cell>::iterator i = this->organism->cells.begin(); i != this->organism->cells.end(); i++)
				execute(i->second);
			flush();
		}
	}

	/// Returns the organism that is currently stored.
	std::map<Coordinates, Cell> &get_organism()
	{
		return this->organism->cells;
	}
};
