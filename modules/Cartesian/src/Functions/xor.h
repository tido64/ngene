#ifndef XOR_H_
#define XOR_H_

class bit_xor : public Function
{
public:
	unsigned char exec(const unsigned char a, const unsigned char b, const unsigned char ctrl)
	{
		return a ^ b;
	}
};

#endif
