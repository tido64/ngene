#include "Gene.h"

using std::random_shuffle;

Gene::Gene(const Setup *s, Random *r) : random(r), setup(s)
{
	// generate a random bitstring
	this->sequence = r->next_int(2 << this->setup->gene_sequence_length);

	// initiate conditions for a comfortable environment
	this->protein.chemical_criteria.reserve(this->setup->cell_types_number);
	for (unsigned int i = 0; i < this->setup->cell_types_number; i++)
		this->protein.chemical_criteria.push_back(
			(r->next() < 0.5) ? 0.0 : r->next() / 10.0);

	// initiate conditions for a thriving neighbourhood
	this->protein.neighbourhood_criteria.reserve(DIRECTIONS);
	for (unsigned int i = 0; i < this->setup->dont_care_neighbours; i++)
		this->protein.neighbourhood_criteria.push_back(static_cast<int>(CellType::any));
	for (unsigned int i = this->setup->dont_care_neighbours; i < DIRECTIONS; i++)
		this->protein.neighbourhood_criteria.push_back(
			r->next_int(
				static_cast<int>(CellType::empty),
				static_cast<int>(this->setup->cell_types_number)));
	random_shuffle(
		this->protein.neighbourhood_criteria.begin(),
		this->protein.neighbourhood_criteria.end(),
		*r);

	this->protein.life = r->next_int(this->setup->max_protein_lifespan);
	this->protein.type = r->next_int(ProteinType::number_of_types);

	switch(this->protein.type)
	{
		case ProteinType::mitotic:
			this->protein.parameters.reserve(DIRECTIONS);
			for (unsigned int i = 0; i < DIRECTIONS; i++)
				this->protein.parameters.push_back(
					(r->next() < 0.5) ? 0.0 : r->next(this->setup->min_stimuli, this->setup->max_stimuli));
			break;
		case ProteinType::regulatory:
			this->protein.parameters.reserve(this->setup->cell_types_number);
			for (unsigned int i = 0; i < this->setup->cell_types_number; i++)
				this->protein.parameters.push_back(
					(r->next() < 0.5) ? 0.0 : r->next(this->setup->min_stimuli, this->setup->max_stimuli));
			break;
		case ProteinType::metamorphic:
			this->protein.parameters.push_back(r->next(this->setup->min_stimuli, this->setup->max_stimuli));
			this->protein.meta = r->next_int(this->setup->cell_types_number);
			break;
		case ProteinType::transcribing:
			this->protein.meta = r->next_int(2 << this->setup->promoter_length);
			break;
	}
}

Gene::Gene(const Gene &g) : random(g.random), sequence(g.sequence), protein(g.protein), setup(g.setup) { }

const Protein *Gene::get_protein()
{
	return &this->protein;
}

unsigned int Gene::get_sequence()
{
	return this->sequence;
}

void Gene::mutate()
{
	// Enter switch of DOOM!
	switch (this->random->next_int(Mutable::number_of_properties))
	{
		case Mutable::sequence: // mutate the dna sequence of this gene
			this->sequence = ngene::bitstring_flip(this->sequence, this->random->next_int(this->setup->gene_sequence_length));
			break;
		case Mutable::lifespan: // increase or decrease the lifespan of the protein
			if ((this->protein.life == 0) | (this->random->next() < 0.5))
				this->protein.life++;
			else
				this->protein.life--;
			break;
		case Mutable::promoter: // flip a bit in the promoter
			if (this->protein.type == ProteinType::transcribing)
				this->protein.meta = ngene::bitstring_flip(this->protein.meta, this->random->next_int(this->setup->promoter_length));
			break;
		case Mutable::thresholds: // mutates the chemical criteria
			this->protein.chemical_criteria[this->random->next_int(this->protein.chemical_criteria.size())]
				+= this->random->next(-0.1, 0.1);
			break;
		case Mutable::neighbourhood: // mutates the neighbourhood criteria
			this->protein.neighbourhood_criteria[this->random->next_int(this->protein.neighbourhood_criteria.size())]
				= this->random->next_int(CellType::empty, this->setup->cell_types_number);
			break;
		default:
			switch (this->protein.type)
			{
				case ProteinType::mitotic:
					this->protein.parameters[this->random->next_int(this->protein.parameters.size())]
						= (this->random->next() < 0.5) ? 0.0 : this->random->next(this->setup->min_stimuli, this->setup->max_stimuli);
					break;
				case ProteinType::regulatory:
					this->protein.parameters[this->random->next_int(this->protein.parameters.size())]
						= this->random->next(this->setup->min_stimuli, this->setup->max_stimuli);
					break;
				case ProteinType::metamorphic:
					if (this->random->next() < 0.5) // mutate stimulus level
						this->protein.parameters[0] = this->random->next(this->setup->min_stimuli, this->setup->max_stimuli);
					else // mutate cell type
						this->protein.meta = this->random->next_int(this->setup->cell_types_number);
					break;
				default:
					break;
			}
			break;
	}
}

Gene & Gene::operator =(const Gene &gene)
{
	this->sequence = gene.sequence;
	this->protein = gene.protein;
	return *this;
}
