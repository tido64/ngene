#ifndef MUX_H_
#define MUX_H_

class mux : public Function
{
public:
	mux() : sizeof_int(sizeof(int) * 8) { }

	int exec(const int a, const int b, const int s)
	{
		int mask = 1, z = 0;
		for (unsigned int i = 0; i < this->sizeof_int; i++)
		{
			//z |= ((this->s & mask) != 0) ? (b & mask) : (a & mask);
			z |= ((a & mask) & ~(s & mask)) | ((b & mask) & (s & mask));
			mask <<= 1;
		}
		return z;
	}
private:
	const unsigned int sizeof_int;
};

#endif
