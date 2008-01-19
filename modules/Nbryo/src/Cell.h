/// Code based off Johan Hoeye's [HOYE2006]. Rewritten in C++ for Ngene with
/// modifications, hopefully making things simpler and faster.

#ifndef CELL
#define CELL

#include "CellType.h"
#include "Hormones.h"
#include "Organism.h"
#include "Protein.h"

class Ribosome;

class Cell
{
public:
	const unsigned int MAX_NUMBER_OF_PROTEINS;

	Cell(const std::vector<Gene> *dna, std::vector<Protein *> *p, Coordinates c, int id);
	virtual ~Cell();

	/// Returns the concentration of given hormone.
	double get_hormone_concentration(const Hormone::Type type)
	{
		return this->hormones.get_concentration(type);
	}

	/// Returns the location of this cell.
	Coordinates get_location()
	{
		return this->coordinates;
	}

	/// Returns the type of this cell.
	CellType::Type get_type()
	{
		return this->type;
	}

	/// Notifies all elements inside the cell of a tick so they can perform
	/// their function. The order of operations in this method might change the
	/// outcome. Experimentation is recommended.
	virtual void increment_tick();

	/// Uhh...
	void queue_action();

protected:
	/// Adjusts the hormone concentrations (maybe sending them out?)
	virtual void adjust_hormones();

	/// Divides the cell into two cells.
	virtual void divide();

	/// Regulates the protein level in the cell.
	virtual void regulate_proteins();

	/// Speciates the cell and gives it a distinct function and/or place.
	virtual void speciate();

	/// Directly translates (skipping transcription) genes that contain a given
	/// promoter to create a polypeptide chain.
	///
	/// Note: Need to check whether this is biologically plausible. Also, the
	/// current algorithm doesn't really abide by MAX_NUMBER_OF_PROTEINS.
	/// Though it is true to Johan's code, it should be rewritten.
	virtual void translate(std::string promoter);

private:
	const std::vector<Gene> *dna;
	const int id;
	Coordinates coordinates;
	std::vector<Cell *> neighbourhood;		///< Keeps track of direct neighbours
	CellType::Type type;
	Hormones hormones;
	std::vector<Protein *> active_proteins;	///< Vector of active proteins
	std::vector<std::vector<Protein *>::iterator> dead_proteins;
	std::vector<Protein *> *proteins;		///< Proteins control internal cell states, cell division, speciation and protein production
	Ribosome *ribosome;						///< Ribosomes create proteins
};

#endif
