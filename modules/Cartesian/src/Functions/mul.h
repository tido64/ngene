#ifndef MUL_H_
#define MUL_H_

class mul : public Function
{
public:
	int exec(const int a, const int b)
	{
		return a * b;
	}

	void prep(const int x) { }
};

#endif
