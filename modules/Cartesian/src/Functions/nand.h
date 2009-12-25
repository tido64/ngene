#ifndef NAND_H_
#define NAND_H_

class nand : public Function
{
public:
	unsigned char exec(const unsigned char a, const unsigned char b, const unsigned char ctrl)
	{
		return ~(a & b);
	}
};

#endif
