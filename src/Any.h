/// Dynamic container for ngene. Cannot copy C-style arrays. Not type safe!

#ifndef ANY_H_
#define ANY_H_

#include <cstdlib>
#include <cstring>

class Any
{
public:
	Any() : size(0), ptr(0) { }

	Any(const Any &a) : size(a.size), ptr(malloc(a.size))
	{
		memcpy(ptr, a.ptr, size);
	}

	template<typename T>
	Any(const T &a) : size(sizeof(a)), ptr(malloc(size))
	{
		memcpy(ptr, &a, size);
	}

	~Any()
	{
		if (ptr != 0)
			free(ptr);
	}

	/// Casts and returns a copy of data to type T.
	/// \param a  The data to cast
	template<typename T>
	inline T cast ()
	{
		return *static_cast<T *>(ptr);
	}

	/// Casts and returns a copy of data to type T.
	/// \param a  The data to cast
	template<class T>
	static inline T cast (const Any &a)
	{
		return *static_cast<T *>(a.ptr);
	}

	Any &operator =(const Any &a)
	{
		copy(a.size, a.ptr);
		return *this;
	}

	template<typename T>
	Any &operator =(const T &a)
	{
		copy(sizeof(a), &a);
		return *this;
	}

private:
	unsigned int size;
	void *ptr;

	/// Makes a copy of data.
	/// \param s  Size of data to copy
	/// \param p  Pointer to data to copy
	inline void copy(const unsigned int s, const void *p)
	{
		if (ptr != 0)
			free(ptr);
		size = s;
		ptr = malloc(size);
		memcpy(ptr, p, size);
	}
};

#endif
