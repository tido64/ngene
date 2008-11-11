#ifndef MUL_H_
#define MUL_H_

class mul : public Function
{
public:
	unsigned char exec(const unsigned char a, const unsigned char b, const unsigned char ctrl)
	{
		return a * b;
	}
};

#endif
