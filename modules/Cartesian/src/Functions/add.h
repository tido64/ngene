#ifndef ADD_H_
#define ADD_H_

class add : public Function
{
public:
	unsigned char exec(const unsigned char a, const unsigned char b, const unsigned char ctrl)
	{
		return a + b;
	}
};

#endif
