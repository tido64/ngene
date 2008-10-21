#ifndef NAND_H_
#define NAND_H_

class nand : public Function
{
public:
	int exec(const int a, const int b, const int ctrl)
	{
		return ~(a & b);
	}
};

#endif
