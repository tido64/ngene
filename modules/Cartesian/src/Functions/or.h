#ifndef OR_H_
#define OR_H_

class bit_or : public Function
{
public:
	unsigned char exec(const unsigned char a, const unsigned char b, const unsigned char ctrl)
	{
		return a | b;
	}
};

#endif
