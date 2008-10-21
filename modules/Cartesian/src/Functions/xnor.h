#ifndef XNOR_H_
#define XNOR_H_

class xnor : public Function
{
public:
	int exec(const int a, const int b, const int ctrl)
	{
		return ~(a ^ b);
	}
};

#endif
