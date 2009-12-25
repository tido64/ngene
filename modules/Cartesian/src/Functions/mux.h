#ifndef MUX_H_
#define MUX_H_

class mux : public Function
{
public:
	mux() : bits(sizeof(unsigned char) * 8) { }

	unsigned char exec(const unsigned char a, const unsigned char b, const unsigned char s)
	{
		unsigned char mask = 1, z = 0;
		for (unsigned int i = 0; i < this->bits; i++)
		{
			z |= ((a & mask) & ~(s & mask)) | ((b & mask) & (s & mask));
			mask <<= 1;
		}
		return z;
	}
private:
	const unsigned int bits;
};

#endif
