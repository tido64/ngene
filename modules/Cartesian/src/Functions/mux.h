#ifndef MUX_H_
#define MUX_H_

class mux : public Function
{
public:
	mux() : sizeof_int(sizeof(int) * 8) { }

	int exec(const int a, const int b)
	{
		int mask = 1, z = 0;
		for (unsigned int i = 0; i < this->sizeof_int; i++)
		{
			//z |= ((this->s & mask) != 0) ? (b & mask) : (a & mask);
			z |= ((a & mask) & ~(this->s & mask)) | ((b & mask) & (this->s & mask));
			mask <<= 1;
		}
		return z;
	}

	void prep(const int s)
	{
		this->s = s;
	}

private:
	const unsigned int sizeof_int;
	int s;
};

#endif
