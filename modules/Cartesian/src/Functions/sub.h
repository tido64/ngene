#ifndef SUB_H_
#define SUB_H_

class sub : public Function
{
public:
	int exec(const int a, const int b, const int ctrl)
	{
		return a - b;
	}
};

#endif
