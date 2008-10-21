#ifndef DIV_H_
#define DIV_H_

class div : public Function
{
public:
	int exec(const int a, const int b, const int ctrl)
	{
		return a / b;
	}
};

#endif
