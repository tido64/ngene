#ifndef NOR_H_
#define NOR_H_

class nor : public Function
{
public:
	unsigned char exec(const unsigned char a, const unsigned char b, const unsigned char ctrl)
	{
		return ~(a | b);
	}
};

#endif
