#ifndef SETUP_H_
#define SETUP_H_

struct Setup
{
	unsigned int
		cell_types_number,
		chemicals_number,
		dont_care_neighbours,
		genes_number,
		gene_sequence_length,
		max_protein_lifespan,
		promoter_length;
	double
		max_stimuli,
		min_stimuli;
};

#endif
