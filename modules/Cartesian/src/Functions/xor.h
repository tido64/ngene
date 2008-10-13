#ifndef XOR_H_
#define XOR_H_

class bit_xor : public Function
{
public:
	int exec(const int a, const int b)
	{
		return a ^ b;
	}

	void prep(const int x) { }
};

#endif
