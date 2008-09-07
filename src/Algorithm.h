/// Convenience header containing often used algorithms.

#ifndef NGENE_ALGORITHM
#define NGENE_ALGORITHM

namespace Ngene
{
	/// Searches for an occurrence of a substring inside a bitstring. Algorithm
	/// makes use of bit-operations.
	/// \param needle        The substring to find
	/// \param needle_size   The number of digits in the needle
	/// \param haystack      The bitstring to search in
	/// \param haystack_size The number of digits in the haystack
	/// \return The index of the first occurrence, or -1 when the substring is not found
	int bitstring_find(unsigned int needle, unsigned int needle_size, unsigned int haystack, unsigned int haystack_size);

	/// Flips a single bit in a bitstring.
	/// \param bits       The bitstring to perform a flip on
	/// \param flip_index The bit to flip
	/// \return The bitstring with a flipped bit at given index
	inline unsigned int bitstring_flip(unsigned int bits, unsigned int flip_index)
	{
		return bits ^ (1 << flip_index);
	}
}

#endif
