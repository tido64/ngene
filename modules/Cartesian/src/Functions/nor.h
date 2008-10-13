#ifndef NOR_H_
#define NOR_H_

class nor : public Function
{
public:
	int exec(const int a, const int b)
	{
		return ~(a | b);
	}

	void prep(const int x) { }
};

#endif
