#include "../../../src/Development/AbstractDevelopment.h"
#include "../../../src/Development/Organism.h"
#include "Gene.h"
#include "ProteinType.h"

typedef std::vector< std::list<Protein>::iterator > ProteinListIterators;
typedef std::vector<Gene> Genome;

class ArtDev3D : public AbstractDevelopment
{
private:
	const unsigned int max_protein_number;	///< The highest number of proteins in a cell
	unsigned int cell_types;				///< The number of cell types
	const double
		max_chemical_concentration,			///< The highest number of chemical concentration
		min_chemical_concentration,			///< The lowest number of chemical concentration
		min_stimuli_level;					///< The minimum stimuli threshold to activate a protein
	std::map<Coordinates, Cell> new_cells;	///< Array of new cells to add to the organism after a tick
	Genome genome;							///< Translated genotype (casted from boost::any)

	/// Part of mitosis(), performs the actual cell duplication and inserts the
	/// new cell into given location if possible. No cells are created if the
	/// given location is already occupied by another cell.
	void cell_division(Cell &cell, const Coordinates &location);

	/// Speciates the cell and gives it a distinct function and/or place. The
	/// stimuli provided by the proteins are first accumulated. The cell type
	/// with the highest stimulus must then exceed a threshold before the cell
	/// morphs into given type.
	void metamorphosis(Cell &cell, ProteinListIterators &activated_proteins);

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
	/// boundaries set in the beginning.
	void mitosis(Cell &cell, ProteinListIterators &activated_proteins);

	/// Regulates the chemical levels in the cell.
	void regulate_chemical_levels(Cell &cell, ProteinListIterators &activated_proteins);

	/// Transcribes the genes that contain a given promoter to create a new
	/// polypeptide chain, ie. protein.
	void transcribe_proteins(Cell &cell, ProteinListIterators &activated_proteins);

public:
	ArtDev3D(int ticks, unsigned int ctypes, double min_stimuli) :
		AbstractDevelopment(ticks),
		max_protein_number(99),
		cell_types(ctypes),
		max_chemical_concentration(1.0),
		min_chemical_concentration(0.0),
		min_stimuli_level(min_stimuli) { }

	void execute(Cell &);
	void initialize(Organism *);
};
