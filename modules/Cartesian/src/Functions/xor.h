#ifndef XOR_H_
#define XOR_H_

class bit_xor : public Function
{
public:
	int exec(const int a, const int b, const int ctrl)
	{
		return a ^ b;
	}
};

#endif
