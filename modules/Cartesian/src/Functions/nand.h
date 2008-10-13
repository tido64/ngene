#ifndef NAND_H_
#define NAND_H_

class nand : public Function
{
public:
	int exec(const int a, const int b)
	{
		return ~(a & b);
	}

	void prep(const int x) { }
};

#endif
