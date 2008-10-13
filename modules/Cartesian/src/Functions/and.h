#ifndef AND_H_
#define AND_H_

class bit_and : public Function
{
public:
	int exec(const int a, const int b)
	{
		return a & b;
	}

	void prep(const int x) { }
};

#endif
