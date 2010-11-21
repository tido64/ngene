/// A grid data structure. Stores data in a perceived two- or three-dimensional
/// static array. There is no re-allocation to a bigger grid as the problem
/// breaks down to where to align the existing data.

#ifndef GRID_H_
#define GRID_H_

template<class T>
class Grid
{
public:
	enum Error
	{
		INVALID_DIMENSIONS,
		X_INDEX_OUT_OF_BOUNDS,
		Y_INDEX_OUT_OF_BOUNDS,
		Z_INDEX_OUT_OF_BOUNDS,
		INDEX_OUT_OF_BOUNDS
	};

	const unsigned int width;   ///< Width of the grid
	const unsigned int height;  ///< Height of the grid
	const unsigned int depth;   ///< Depth of the grid
	const unsigned int size;    ///< Size of the array

	/// Constructs a two- or three-dimensional grid.
	/// \param w  Width of the grid
	/// \param h  Height of the grid
	/// \param d  Depth of the grid (default is 1)
	Grid(const int w, const int h, const int d = 1) :
		width(w), height(h), depth(d), size(w * h * d), slice(w * h), array(0)
	{
		if (w < 1 || h < 1 || d < 1) throw INVALID_DIMENSIONS;

		this->array = new T[this->size];
	}

	~Grid() { delete[] this->array; }

	/// Returns the element stored at (n).
	inline T& operator() (const unsigned int n)
	{
		if (n > this->size) throw INDEX_OUT_OF_BOUNDS;

		return this->array[n];
	}

	/// Returns the element stored at (x,y).
	inline T& operator() (const unsigned int x, const unsigned int y)
	{
		if (x > this->width) throw X_INDEX_OUT_OF_BOUNDS;
		if (y > this->height) throw Y_INDEX_OUT_OF_BOUNDS;

		return this->array[this->height * y + x];
	}

	/// Returns the element stored at (x,y,z).
	inline T& operator() (const unsigned int x, const unsigned int y, const unsigned int z)
	{
		if (x > this->width) throw X_INDEX_OUT_OF_BOUNDS;
		if (y > this->height) throw Y_INDEX_OUT_OF_BOUNDS;
		if (z > this->depth) throw Z_INDEX_OUT_OF_BOUNDS;

		return this->array[this->slice * z + this->height * y + x];
	}

private:
	const unsigned int slice;  ///< Number of elements of a slice or face of the grid
	T *array;                  ///< The grid is stored in this array
};

#endif
