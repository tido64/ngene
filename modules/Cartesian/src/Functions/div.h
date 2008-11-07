#ifndef DIV_H_
#define DIV_H_

class div : public Function
{
public:
	int exec(const int a, const int b, const int ctrl)
	{
		return (b == 0) ? 0 : a / b;
	}
};

#endif
