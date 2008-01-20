/// Code based off Johan Høye's [HOYE2006]. Rewritten in C++ for Ngene with
/// modifications, hopefully making things simpler and faster.
///
/// The purpose of ProteinAction.java and the algorithms using it, is now 
/// served by the idea of an active protein and the cell's ability to "read"
/// them in different situations.

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
	const unsigned int MAX_NUMBER_OF_PROTEINS;						///< The maximum amount of proteins allowed
	const double STIMULUS_THRESHOLD;								///< The level of stimulus at which this cell will react

	Cell(int id, Organism *host, Coordinates c, std::vector<Protein *> *p);
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

	std::vector<Protein *> *get_proteins()
	{
		return this->proteins;
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

protected:
	/// The mitotic phase refers to mitosis and cytokinesis in which (1) a
	/// mother cell duplicates its chromosomes in the nucleus and (2) divides
	/// it along with cytoplasm, organelles and cell membrane into two daughter
	/// cells.
	///
	/// Remarks:
	/// - Johan's code dictates that all stimuli in any direction should be
	/// "executed", meaning if all six directions were above the stimulus
	/// threshold, the cell would divide in all six directions. Biologically,
	/// this is not plausible.
	/// - Cell division is bound by occupancy of the location and the
	/// boundaries set in the beginning. The latter may give an unwanted effect
	/// as it is not part of anything biological.
	virtual void mitosis();

	/// Adjusts the hormone concentrations (by secretion?)
	virtual void regulate_hormones();

	/// Regulates the protein level in the cell. Basically removes dead
	/// proteins and marks the active ones.
	virtual void regulate_proteins();

	/// Speciates the cell and gives it a distinct function and/or place. The
	/// stimuli provided by the proteins are first accumulated. The cell type
	/// with the highest stimulus must then exceed a threshold before the cell
	/// morphs into given type.
	virtual void speciate();

	/// Directly translates (skipping transcription) genes that contain a given
	/// promoter to create a polypeptide chain.
	virtual void translate();

private:
	const int id;
	const std::vector<Gene> *dna;									///< The dna of the organism this cell is part of
	CellType::Type type;											///< The type of this cell
	Coordinates coordinates;										///< The location of this cell
	std::vector<Cell *> neighbourhood;								///< Keeps track of direct neighbours
	Hormones hormones;												///< Hormones regulate protein activity
	Organism *organism;												///< The organism this cell is part of
	std::vector<std::vector<Protein *> > active_proteins;			///< Vector of categorized active proteins
	std::vector<std::vector<Protein *>::iterator> dead_proteins;	///< Vector of dead proteins to be removed
	std::vector<Protein *> *proteins;								///< Proteins control internal cell states, cell division, speciation and protein production
	Ribosome *ribosome;												///< Ribosomes create proteins
};

#endif
