#include "Cartesian.h"

using std::map;
using std::vector;

Cartesian::Cartesian(const unsigned int t, const unsigned int l, const unsigned int n) :
	AbstractDevelopment(t), l(l), n(n), MAX_CHEMICALS(255)
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
	double sum (0);
	for (vector<Message>::const_iterator i = in.begin(); i != in.end(); i++)
		sum += i->chemicals[0];
	return (lvl / 2) + (sum / 16);
}

void Cartesian::execute(Cell &c)
{
	vector<unsigned int> input ((From::ALL_NEIGHBOURS + 1) * 4);
	input.push_back(static_cast<unsigned int>(c.messages[From::above_left].chemicals[0]));
	input.push_back(static_cast<unsigned int>(c.messages[From::above].chemicals[0]));
	input.push_back(static_cast<unsigned int>(c.messages[From::above_right].chemicals[0]));
	input.push_back(static_cast<unsigned int>(c.messages[From::left].chemicals[0]));
	input.push_back(static_cast<unsigned int>(c.chemicals[0]));
	input.push_back(static_cast<unsigned int>(c.messages[From::right].chemicals[0]));
	input.push_back(static_cast<unsigned int>(c.messages[From::below_left].chemicals[0]));
	input.push_back(static_cast<unsigned int>(c.messages[From::below].chemicals[0]));
	input.push_back(static_cast<unsigned int>(c.messages[From::below_right].chemicals[0]));
	input.push_back(c.messages[From::above_left].type);
	input.push_back(c.messages[From::above].type);
	input.push_back(c.messages[From::above_right].type);
	input.push_back(c.messages[From::left].type);
	input.push_back(c.type);
	input.push_back(c.messages[From::right].type);
	input.push_back(c.messages[From::below_left].type);
	input.push_back(c.messages[From::below].type);
	input.push_back(c.messages[From::below_right].type);

	for (unsigned int i = 0; i < this->nodes.size(); i += this->n + 1)
		input.push_back(this->system[this->nodes[i + 3]]->exec(input[this->nodes[i]], input[this->nodes[i + 1]], input[this->nodes[i + 2]]));

	// handle output
	unsigned int mask (1);
	c.type = input[this->output[0]];

	if ((this->output[1] & mask) != 0)
		divide_cell(c, c.coords.above_left()).chemicals[0] = input[this->output[From::above_left + 2]];
	mask <<= 1;

	if ((this->output[1] & mask) != 0)
		divide_cell(c, c.coords.above()).chemicals[0] = input[this->output[From::above + 2]];
	mask <<= 1;

	if ((this->output[1] & mask) != 0)
		divide_cell(c, c.coords.above_right()).chemicals[0] = input[this->output[From::above_right + 2]];
	mask <<= 1;

	if ((this->output[1] & mask) != 0)
		divide_cell(c, c.coords.left()).chemicals[0] = input[this->output[From::left + 2]];
	mask <<= 1;

	if ((this->output[1] & mask) != 0)
		divide_cell(c, c.coords.right()).chemicals[0] = input[this->output[From::right + 2]];
	mask <<= 1;

	if ((this->output[1] & mask) != 0)
		divide_cell(c, c.coords.below_left()).chemicals[0] = input[this->output[From::below_left + 2]];
	mask <<= 1;

	if ((this->output[1] & mask) != 0)
		divide_cell(c, c.coords.below()).chemicals[0] = input[this->output[From::below + 2]];
	mask <<= 1;

	if ((this->output[1] & mask) != 0)
		divide_cell(c, c.coords.below_right()).chemicals[0] = input[this->output[From::below_right + 2]];
	mask <<= 1;
}

void Cartesian::initialize(Organism *o)
{
	static const int output_nodes (10);

	// extract indices for the input
	this->nodes.clear();
	for (unsigned int i = 0; i < o->genotype.size() - output_nodes; i++)
	{
		// BUG: casting fails because it mixes up the signs?
		printf(" %d", i);
		this->nodes.push_back(boost::any_cast<int>(o->genotype[i]));
	}

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
