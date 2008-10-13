#include "Cartesian.h"

using std::map;
using std::vector;

Cartesian::Cartesian(const unsigned int t, const unsigned int l, const unsigned int n) :
	AbstractDevelopment(t), l(l), n(n), system(NUMBER_OF_FUNCTIONS)
{
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
	vector<int> input ((From::ALL_NEIGHBOURS + 1) << 2);
	input.push_back(static_cast<int>(c.messages[From::above_left].chemicals[0]));
	input.push_back(static_cast<int>(c.messages[From::above].chemicals[0]));
	input.push_back(static_cast<int>(c.messages[From::above_right].chemicals[0]));
	input.push_back(static_cast<int>(c.messages[From::left].chemicals[0]));
	input.push_back(static_cast<int>(c.chemicals[0]));
	input.push_back(static_cast<int>(c.messages[From::right].chemicals[0]));
	input.push_back(static_cast<int>(c.messages[From::below_left].chemicals[0]));
	input.push_back(static_cast<int>(c.messages[From::below].chemicals[0]));
	input.push_back(static_cast<int>(c.messages[From::below_right].chemicals[0]));
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
	{
		this->system[this->nodes[i + 3]]->prep(this->nodes[i + 2]);
		input.push_back(this->system[this->nodes[i + 3]]->exec(this->nodes[i], this->nodes[i + 1]));
	}
}

void Cartesian::initialize(Organism *o)
{
	this->nodes.clear();
	for (vector<boost::any>::const_iterator i = o->genotype.begin(); i != o->genotype.end(); i++)
		this->nodes.push_back(boost::any_cast<unsigned int>(*i));

	// first cell
}
