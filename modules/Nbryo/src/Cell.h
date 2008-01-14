/// Code based off Johan Høye's [HOYE2006]. Rewritten in C++ for Ngene with
/// modifications, hopefully making things simpler and faster.

#ifndef CELL
#define CELL

#include "CellType.h"
#include "Coordinates.h"
#include "Hormones.h"
#include "Proteins.h"
#include "Ribosome.h"

class Ribosome;

class Cell
{
public:
	const int MAX_NUMBER_OF_PROTEINS;

	Cell(const std::vector<Gene> *dna, Proteins *p, Coordinates c, int id);
	~Cell();

	/// Returns the type of this cell.
	CellType::Type get_type() { return this->type; }

	/// Returns the location of this cell.
	const Coordinates &get_location() { return this->coordinates; }

	/// Returns the hormone concentrations in this cell.
	const Hormones *get_hormones() { return &this->hormones; }

	/// Notifies all elements inside the cell of a tick.
	virtual void increment_tick();

	/// Uhh...
	void queue_action();

protected:
	Cell();

	/// Adjusts the hormone concentrations (maybe sending them out?)
	virtual void adjust_hormones();

	/// Divides the cell into two cells.
	virtual void divide();

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
	std::vector<Cell *> neighbourhood;	///< Keeps track of direct neighbours
	CellType::Type type;
	Hormones hormones;
	Proteins *proteins;					///< Proteins control internal cell states, cell division, speciation and protein production
	Ribosome *ribosome;					///< Ribosomes create proteins
};

#endif
