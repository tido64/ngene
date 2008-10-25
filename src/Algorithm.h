/// Convenience header containing often used algorithms.

#ifndef ALGORITHM_H_
#define ALGORITHM_H_

#include <cmath>
#include <sstream>

namespace ngene
{
	const double ln2 = log(2.0);	///< Constant used to convert log base 10 to base 2

	/// Searches for an occurrence of a substring inside a bitstring. Algorithm
	/// makes use of bit-operations.
	/// \param needle         The substring to find
	/// \param needle_size    The number of digits in the needle
	/// \param haystack       The bitstring to search in
	/// \param haystack_size  The number of digits in the haystack
	/// \return The index of the first occurrence, or -1 when the substring is not found
	int bitstring_find(unsigned int needle, unsigned int needle_size, unsigned int haystack, unsigned int haystack_size);

	/// Flips a single bit in a bitstring.
	/// \param bits        The bitstring to perform a flip on
	/// \param flip_index  The bit to flip
	/// \return The bitstring with a flipped bit at given index
	inline unsigned int bitstring_flip(unsigned int bits, unsigned int flip_index)
	{
		return bits ^ (1 << flip_index);
	}

	/// Returns the logarithm base 2 of a number.
	inline double log2(const unsigned int x)
	{
		return log(static_cast<double>(x)) / ln2;
	}

	/// Converts any basic data type to string.
	template <class T>
	inline std::string to_string(const T& t)
	{
		std::stringstream ss;
		ss << t;
		return ss.str();
	}
}

#endif
