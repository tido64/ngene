#ifndef DIV_H_
#define DIV_H_

class div : public Function
{
public:
	unsigned char exec(const unsigned char a, const unsigned char b, const unsigned char ctrl)
	{
		return (b == 0) ? 0 : a / b;
	}
};

#endif
