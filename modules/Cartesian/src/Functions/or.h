#ifndef OR_H_
#define OR_H_

class bit_or : public Function
{
public:
	int exec(const int a, const int b, const int ctrl)
	{
		return a | b;
	}
};

#endif
