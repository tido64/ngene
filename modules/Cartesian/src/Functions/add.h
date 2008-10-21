#ifndef ADD_H_
#define ADD_H_

class add : public Function
{
public:
	int exec(const int a, const int b, const int ctrl)
	{
		return a + b;
	}
};

#endif
