#ifndef NOR_H_
#define NOR_H_

class nor : public Function
{
public:
	int exec(const int a, const int b, const int ctrl)
	{
		return ~(a | b);
	}
};

#endif
