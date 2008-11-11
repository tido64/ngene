#ifndef AND_H_
#define AND_H_

class bit_and : public Function
{
public:
	unsigned char exec(const unsigned char a, const unsigned char b, const unsigned char ctrl)
	{
		return a & b;
	}
};

#endif
