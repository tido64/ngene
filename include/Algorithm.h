/// Convenience header containing often used algorithms.

#ifndef ALGORITHM_H_
#define ALGORITHM_H_

#include <cmath>
#include <sstream>

namespace ngene
{
	const double ln2 = log(2.0);	///< Constant used to convert log base 10 to base 2
	const std::string whitespace (" \t\n\v\f\r");

	/// Searches for an occurrence of a substring inside a bitstring. Algorithm
	/// makes use of bit-operations.
	/// \param needle         The substring to find
	/// \param needle_size    The number of digits in the needle
	/// \param haystack       The bitstring to search in
	/// \param haystack_size  The number of digits in the haystack
	/// \return The index of the first occurrence, or -1 when the substring is not found
	inline int bitstring_find(unsigned int needle, const unsigned int needle_size, const unsigned int haystack, const unsigned int haystack_size)
	{
		for (unsigned int i = 0; i <= haystack_size - needle_size; i++)
		{
			if ((haystack & needle) == needle)
				return i;
			needle <<= 1;
		}
		return -1;
	}

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

	/// Converts any POD type to string.
	template <typename T>
	inline std::string to_string(const T &t)
	{
		std::stringstream ss;
		ss << t;
		return ss.str();
	}

	/// Trims whitespaces from a string.
	inline std::string trim(std::string str)
	{
		str = str.erase(str.find_last_not_of(whitespace) + 1);
		str = str.erase(0, str.find_first_not_of(whitespace));
		return str;
	}
}

#endif
