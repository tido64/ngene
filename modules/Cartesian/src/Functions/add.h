#ifndef ADD_H_
#define ADD_H_

class add : public Function
{
public:
	int exec(const int a, const int b)
	{
		return a + b;
	}

	void prep(const int x) { }
};

#endif
