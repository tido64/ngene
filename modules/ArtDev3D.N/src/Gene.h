/// Code based off Johan Høye's [HOYE2006]. Rewritten in C++ for Ngene with
/// modifications, hopefully making things simpler and faster.
///
/// The gene is a dna sequence that codes a protein. The sequence includes a
/// promoter that a protein recognizes and triggers an action. The translation
/// of this gene is done beforehand to reduce cpu cycles.

#ifndef GENE
#define GENE

#define DIRECTIONS 6

#include "../../../src/Development/Protein.h"
#include "../../../src/Random.h"
#include <algorithm>
#include <boost/dynamic_bitset.hpp>
#include "CellType.h"
#include "Mutable.h"
#include "ProteinType.h"
#include "Setup.h"

class Gene
{
private:
	boost::dynamic_bitset<> sequence;
	const Setup setup;
	Protein protein;

public:
	Gene(const Setup &s, const Genotype &g) :
		sequence(s.gene_sequence_length),
		setup(s)
	{
		for (unsigned int i = 0; i < this->setup.gene_sequence_length; i++)
			this->sequence[i] = Random::Instance().next() < 0.5;

		// initiate conditions for a comfortable environment
		this->protein.chemical_criteria.reserve(this->setup.cell_type_number);
		for (unsigned int i = 0; i < this->setup.cell_type_number; i++)
			this->protein.chemical_criteria.push_back(
				(Random::Instance().next() < 0.5) ? 0.0 : Random::Instance().next() / 10.0);

		// initiate conditions for a thriving neighbourhood
		this->protein.neighbourhood_criteria.reserve(DIRECTIONS);
		for (unsigned int i = 0; i < this->setup.dont_care_neighbours; i++)
			this->protein.neighbourhood_criteria.push_back(static_cast<int>(CellType::any));
		for (unsigned int i = this->setup.dont_care_neighbours; i < DIRECTIONS; i++)
			this->protein.neighbourhood_criteria.push_back(
				Random::Instance().next_int(
					static_cast<int>(CellType::empty),
					static_cast<int>(this->setup.cell_type_number)));
		std::random_shuffle(
			this->protein.neighbourhood_criteria.begin(),
			this->protein.neighbourhood_criteria.end(),
			Random::Instance());

		this->protein.type = Random::Instance().next_int(ProteinType::number_of_types);

		switch(this->protein.type)
		{
			case ProteinType::mitotic:
				this->protein.parameters.reserve(DIRECTIONS);
				for (unsigned int i = 0; i < DIRECTIONS; i++)
					this->protein.parameters.push_back(
						(Random::Instance().next() < 0.5) ? 0.0 : Random::Instance().next(this->setup.min_stimuli, this->setup.max_stimuli));
				break;
			case ProteinType::regulatory:
				this->protein.parameters.reserve(this->setup.cell_type_number);
				for (unsigned int i = 0; i < this->setup.cell_type_number; i++)
					this->protein.parameters.push_back(
						(Random::Instance().next() < 0.5) ? 0.0 : Random::Instance().next(this->setup.min_stimuli, this->setup.max_stimuli));
				break;
			case ProteinType::speciation:
				this->protein.parameters.push_back(Random::Instance().next(this->setup.min_stimuli, this->setup.max_stimuli));
				this->protein.meta = Random::Instance().next_int(this->setup.cell_type_number);
				break;
			case ProteinType::transcribing:
				this->protein.meta = Random::Instance().next_int(2 << this->setup.promoter_length);
				break;
		}
	}

	Gene(const Gene &g) : sequence(g.sequence), setup(g.setup), protein(g.protein) { }

	/// Randomly mutates a property of this gene (and effectively the protein).
	/// Currently, there are no way to check that the mutated values are not
	/// out of bounds. Time will tell whether this is disadvantageous or
	/// beneficial.
	void mutate()
	{
		// Enter switch of DOOM!
		switch (Random::Instance().next_int(Mutable::number_of_properties))
		{
			case Mutable::sequence: // mutate the dna sequence of this gene
				this->sequence.flip(Random::Instance().next_int(this->sequence.size()));
				break;
			case Mutable::lifespan: // increase/decrease lifespan of proteins
				if ((this->protein.life == 0) | (Random::Instance().next() < 0.5))
					this->protein.life++;
				else
					this->protein.life--;
				break;
			case Mutable::thresholds: // mutates the chemical criteria
				this->protein.chemical_criteria[Random::Instance().next_int(this->protein.chemical_criteria.size())]
					+= Random::Instance().next(-0.1, 0.1);
				break;
			case Mutable::neighbourhood:
				this->protein.neighbourhood_criteria[Random::Instance().next_int(this->protein.neighbourhood_criteria.size())]
					= Random::Instance().next_int(CellType::empty, this->setup.cell_type_number);
				break;
			default:
				switch (this->protein.type)
				{
					case ProteinType::mitotic:
						this->protein.parameters[Random::Instance().next_int(this->protein.parameters.size())]
							= (Random::Instance().next() < 0.5) ? 0.0 : Random::Instance().next(this->setup.min_stimuli, this->setup.max_stimuli);
						break;
					case ProteinType::regulatory:
						this->protein.parameters[Random::Instance().next_int(this->protein.parameters.size())]
							= Random::Instance().next(this->setup.min_stimuli, this->setup.max_stimuli);
						break;
					case ProteinType::speciation:
						if (Random::Instance().next() < 0.5) // mutate stimulus level
							this->protein.parameters[0] = Random::Instance().next(this->setup.min_stimuli, this->setup.max_stimuli);
						else // mutate cell type
							this->protein.meta = Random::Instance().next_int(this->setup.cell_type_number);
						break;
					case ProteinType::transcribing: // flip a random bit in the promoter
						this->protein.meta ^= 1 << Random::Instance().next_int(this->setup.promoter_length);
						break;
					default:
						break;
				}
				break;
		}
	}

	Gene &operator =(const Gene &gene)
	{
		this->sequence = gene.sequence;
		this->protein = gene.protein;
		return *this;
	}
};

#endif
