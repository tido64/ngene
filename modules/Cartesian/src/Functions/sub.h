#ifndef SUB_H_
#define SUB_H_

class sub : public Function
{
public:
	int exec(const int a, const int b)
	{
		return a - b;
	}

	void prep(const int x) { }
};

#endif
