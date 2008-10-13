#ifndef DIV_H_
#define DIV_H_

class div : public Function
{
public:
	int exec(const int a, const int b)
	{
		return a / b;
	}

	void prep(const int x) { }
};

#endif
