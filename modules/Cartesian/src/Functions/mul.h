#ifndef MUL_H_
#define MUL_H_

class mul : public Function
{
public:
	int exec(const int a, const int b, const int ctrl)
	{
		return a * b;
	}
};

#endif
