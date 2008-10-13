#ifndef OR_H_
#define OR_H_

class bit_or : public Function
{
public:
	int exec(const int a, const int b)
	{
		return a | b;
	}

	void prep(const int x) { }
};

#endif
