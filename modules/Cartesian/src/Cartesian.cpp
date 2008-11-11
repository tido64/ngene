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

void Cartesian::execute(Cell &c)
{
	if (c.type < 1)
	{
		remove(c.coords);
		return;
	}

	unsigned int sigma = 0;
	vector<unsigned char> input (18, 0);
	input.reserve((From::ALL_NEIGHBOURS + 1) * 4);
	input[0] = c.chemicals[0];
	input[9] = c.type;
	for (unsigned int i = 0; i < 8; i++)
	{
		if (c.messages[i].type > 0)
		{
			input[i + 1] = c.messages[i].chemicals[0];
			sigma += c.messages[i].chemicals[0];
			input[i + 10] = c.messages[i].type;
		}
	}

	unsigned char x, y, z;
	for (unsigned int i = 0; i < this->nodes.size(); i += 4)
	{
		x = input[this->nodes[i]];
		y = input[this->nodes[i + 1]];
		z = input[this->nodes[i + 2]];
		input.push_back(this->system[this->nodes[i + 3]]->exec(x, y, z));
	}

	// handle output
	unsigned char mask = 1, node = 2;
	c.type = input[this->output[0]] & 3;

	vector<Coordinates> neighbourhood;
	neighbourhood.push_back(c.coords.above_left());
	neighbourhood.push_back(c.coords.above());
	neighbourhood.push_back(c.coords.above_right());
	neighbourhood.push_back(c.coords.left());
	neighbourhood.push_back(c.coords.right());
	neighbourhood.push_back(c.coords.below_left());
	neighbourhood.push_back(c.coords.below());
	neighbourhood.push_back(c.coords.below_right());

	for (vector<Coordinates>::iterator i = neighbourhood.begin(); i != neighbourhood.end(); i++)
	{
		if ((input[this->output[1]] & mask) != 0) // && !exists(*i))
			divide_cell(c, *i).chemicals[0] = input[this->output[node]];
		mask <<= 1;
		node++;
	}

	c.chemicals[0] = (c.chemicals[0] / 2) + (sigma / 16);
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
