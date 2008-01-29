#include "NUtility.h"

double NUtility::random()
{
	return (double)rand() / ((double)RAND_MAX + 1.0);
}

unsigned int NUtility::random(unsigned int k)
{
	return (unsigned int)(random() * k);
}
