#ifndef XNOR_H_
#define XNOR_H_

class xnor : public Function
{
public:
	unsigned char exec(const unsigned char a, const unsigned char b, const unsigned char ctrl)
	{
		return ~(a ^ b);
	}
};

#endif
