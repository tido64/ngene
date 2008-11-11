#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_

#include "../../../src/Algorithm.h"

class Function
{
public:
	virtual ~Function() { };
	virtual unsigned char exec(const unsigned char, const unsigned char, const unsigned char) = 0;
};

enum Functions
{
	ADD,
	AND,
	DIV,
	MUL,
	MUX,
	NAND,
	NOR,
	OR,
	SUB,
	XNOR,
	XOR,
	NUMBER_OF_FUNCTIONS
};

namespace cgp
{
	#include "Functions/add.h"
	#include "Functions/and.h"
	#include "Functions/div.h"
	#include "Functions/mul.h"
	#include "Functions/mux.h"
	#include "Functions/nand.h"
	#include "Functions/nor.h"
	#include "Functions/or.h"
	#include "Functions/sub.h"
	#include "Functions/xnor.h"
	#include "Functions/xor.h"
}

#endif
