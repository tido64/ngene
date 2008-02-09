/// Code based off Johan Høye's [HOYE2006]. Rewritten in C++ for Ngene with
/// modifications, hopefully making things simpler and faster.
///
/// The purpose of ProteinAction.java and the algorithms using it, is now 
/// served by the idea of an active protein and the cell's ability to "read"
/// them in different situations.

#ifndef CELL
#define CELL

#include "Coordinates.h"
#include "Gene.h"
#include "Hormones.h"
#include "Protein.h"

typedef std::vector<Gene> DNA;

class Organism;
class Ribosome;

class Cell
{
	friend class Ribosome;

public:
	const unsigned int MAX_NUMBER_OF_PROTEINS;						///< The maximum amount of proteins allowed
	const double STIMULUS_THRESHOLD;								///< The level of stimulus at which this cell will perform set action

	/// Used only to create the zygote.
	Cell(Organism *host, const std::vector<Protein> &proteins);

	/// Used by CellFactory to perform cell division.
	Cell(int id, const Cell *mother, const Coordinates &c);

	virtual ~Cell();

	/// Returns the concentration of given hormone.
	double get_hormones(const Hormone::Type type) const;

	/// Returns the location of this cell.
	Coordinates get_location() const;

	/// Returns a vector with the neighbours of this cell
	/// \param[out] neighbourhood Stores the neighbour cell types
	void get_neighbourhood(std::vector<CellType::Type> &neighbourhood) const;

	const std::vector<Protein> *get_proteins() const;

	/// Returns the type of this cell.
	CellType::Type get_type() const;

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
	CellType::Type type;											///< This cell's type
	DNA dna;														///< The dna of the organism this cell is part of
	Coordinates coordinates;										///< The location of this cell
	Hormones hormones;												///< Hormones regulate protein activity
	Organism *organism;												///< The organism this cell is part of
	std::vector<std::vector<Protein *> > active_proteins;			///< Categorized vector of active proteins
	std::vector<std::vector<Protein>::iterator> dead_proteins;		///< Vector of dead proteins to be removed
	std::vector<Protein> proteins;									///< Proteins control internal cell states, cell division, speciation and protein production
	Ribosome *ribosome;												///< Ribosomes create proteins

	/// From Wikipedia: Cytokinesis is a separate process that begins at the
	/// same time as telophase. Cytokinesis is technically not even a phase of
	/// mitosis, but rather a separate process, necessary for completing cell
	/// division.
	///
	/// Here, it's just used to "optimize"/enable future vital operations.
	void engage_cytokinesis();
};

#endif
