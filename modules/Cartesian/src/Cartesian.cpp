#include "Cartesian.h"

using std::map;
using std::vector;

Cartesian::Cartesian(const unsigned int t, const unsigned int l) :
	AbstractDevelopment(t), l(l), MAX_CHEMICALS(255)
{
	this->output.reserve(10);
	this->system.reserve(NUMBER_OF_FUNCTIONS);
	this->system.push_back(new cgp::add());
	this->system.push_back(new cgp::bit_and());
	this->system.push_back(new cgp::div());
	this->system.push_back(new cgp::mul());
	this->system.push_back(new cgp::mux());
	this->system.push_back(new cgp::nand());
	this->system.push_back(new cgp::nor());
	this->system.push_back(new cgp::bit_or());
	this->system.push_back(new cgp::sub());
	this->system.push_back(new cgp::xnor());
	this->system.push_back(new cgp::bit_xor());
}

Cartesian::~Cartesian()
{
	for (vector<Function *>::iterator i = this->system.begin(); i != this->system.end(); i++)
		delete *i;
}

double Cartesian::diffuse(const double lvl, const vector<Message> &in)
{
	double sum = 0;
	for (vector<Message>::const_iterator i = in.begin(); i != in.end(); i++)
		if (i->type > -1)
			sum += i->chemicals[0];
	return (lvl / 2) + (sum / 16);
}

void Cartesian::execute(Cell &c)
{
	vector<unsigned int> input (18, 0);
	input.reserve((From::ALL_NEIGHBOURS + 1) * 4);

	if (c.messages[From::above_left].type != -1)
	{
		input[0] = c.messages[From::above_left].chemicals[0];
		input[9] = c.messages[From::above_left].type;
	}
	if (c.messages[From::above].type != -1)
	{
		input[1] = c.messages[From::above].chemicals[0];
		input[10] = c.messages[From::above].type;
	}

	if (c.messages[From::above_right].type != -1)
	{
		input[2] = c.messages[From::above_right].chemicals[0];
		input[11] = c.messages[From::above_right].type;
	}
	if (c.messages[From::left].type != -1)
	{
		input[3] = c.messages[From::left].chemicals[0];
		input[12] = c.messages[From::left].type;
	}
	input[4] = c.chemicals[0];
	input[13] = c.type;
	if (c.messages[From::right].type != -1)
	{
		input[5] = c.messages[From::right].chemicals[0];
		input[14] = c.messages[From::right].type;
	}
	if (c.messages[From::below_left].type != -1)
	{
		input[6] = c.messages[From::below_left].chemicals[0];
		input[15] = c.messages[From::below_left].type;
	}
	if (c.messages[From::below].type != -1)
	{
		input[7] = c.messages[From::below].chemicals[0];
		input[16] = c.messages[From::below].type;
	}
	if (c.messages[From::below_right].type != -1)
	{
		input[8] = c.messages[From::below_right].chemicals[0];
		input[17] = c.messages[From::below_right].type;
	}

	//printf("==>");
	//for (vector<unsigned int>::iterator i = input.begin(); i != input.end(); i++)
	//	printf(" %u", *i);
	//printf("\n");

	unsigned int x, y, z;
	for (unsigned int i = 0; i < this->nodes.size(); i += 4)
	{
		x = input[this->nodes[i]] & this->MAX_CHEMICALS;
		y = input[this->nodes[i + 1]] & this->MAX_CHEMICALS;
		z = input[this->nodes[i + 2]] & this->MAX_CHEMICALS;
		input.push_back(this->system[this->nodes[i + 3]]->exec(x, y, z));
	}

	// handle output
	unsigned int mask = 1;
	c.type = input[this->output[0]] & 3;

	if (!exists(c.coords.above_left()) && (this->output[1] & mask) != 0)
		divide_cell(c, c.coords.above_left()).chemicals[0] = input[this->output[From::above_left + 2]] & this->MAX_CHEMICALS;
	mask <<= 1;

	if (!exists(c.coords.above()) && (this->output[1] & mask) != 0)
		divide_cell(c, c.coords.above()).chemicals[0] = input[this->output[From::above + 2]] & this->MAX_CHEMICALS;
	mask <<= 1;

	if (!exists(c.coords.above_right()) && (this->output[1] & mask) != 0)
		divide_cell(c, c.coords.above_right()).chemicals[0] = input[this->output[From::above_right + 2]] & this->MAX_CHEMICALS;
	mask <<= 1;

	if (!exists(c.coords.left()) && (this->output[1] & mask) != 0)
		divide_cell(c, c.coords.left()).chemicals[0] = input[this->output[From::left + 2]] & this->MAX_CHEMICALS;
	mask <<= 1;

	if (!exists(c.coords.right()) && (this->output[1] & mask) != 0)
		divide_cell(c, c.coords.right()).chemicals[0] = input[this->output[From::right + 2]] & this->MAX_CHEMICALS;
	mask <<= 1;

	if (!exists(c.coords.below_left()) && (this->output[1] & mask) != 0)
		divide_cell(c, c.coords.below_left()).chemicals[0] = input[this->output[From::below_left + 2]] & this->MAX_CHEMICALS;
	mask <<= 1;

	if (!exists(c.coords.below()) && (this->output[1] & mask) != 0)
		divide_cell(c, c.coords.below()).chemicals[0] = input[this->output[From::below + 2]] & this->MAX_CHEMICALS;
	mask <<= 1;

	if (!exists(c.coords.below_right()) && (this->output[1] & mask) != 0)
		divide_cell(c, c.coords.below_right()).chemicals[0] = input[this->output[From::below_right + 2]] & this->MAX_CHEMICALS;
	mask <<= 1;

	c.chemicals[0] = diffuse(c.chemicals[0], c.messages);
	if (c.chemicals[0] > this->MAX_CHEMICALS)
	{
		printf("==> A cell messed up its chemicals\n");
		exit(-1);
	}
}

void Cartesian::initialize(Organism *o)
{
	static const int output_nodes = 10;

	// extract indices for the input
	this->nodes.clear();
	for (unsigned int i = 0; i < o->genotype.size() - output_nodes; i++)
		this->nodes.push_back(boost::any_cast<unsigned int>(o->genotype[i]));

	// extract indices for the output
	this->output.clear();
	for (unsigned int i = o->genotype.size() - output_nodes; i < o->genotype.size(); i++)
		this->output.push_back(boost::any_cast<unsigned int>(o->genotype[i]));

	// create first cell
	Cell c;
	c.type = 3;	// 00 = empty, 01 = blue, 10 = red, 11 = white
	c.chemicals.push_back(this->MAX_CHEMICALS);
	o->cells[c.coords] = c;
}
