#include "Algorithm.h"

int Ngene::bitstring_find(unsigned int needle, unsigned int needle_size, unsigned int haystack, unsigned int haystack_size)
{
	if (needle_size < haystack_size)
	{
		needle <<= haystack_size - needle_size;
		for (unsigned int i = 0; i < haystack_size - needle_size; i++)
		{
			if ((haystack ^ needle) == 0)
				return i;
			needle >>= 1;
		}
	}
	return -1;
}
