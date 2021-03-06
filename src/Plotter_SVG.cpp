#include "Plotter_SVG.h"

using std::string;
using std::vector;

Plotter_SVG::Plotter_SVG() : fitness_margin(16), fitness_scale(240) { }

Plotter_SVG::~Plotter_SVG()
{
	this->svg << "</svg>\n";
	this->svg.close();
}

bool Plotter_SVG::open(string filename, const Config *config, const vector<const char *> *modules)
{
	filename += ".svg";
	this->svg.open(filename.c_str());
	if (!this->svg.is_open())
		return false;

	// Write start of document
	this->svg	<< "<?xml version=\"1.0\"?>\n"
				<< "<!DOCTYPE svg PUBLIC \"-//W3C//DTD SVG 1.1//EN\" \"http://www.w3.org/Graphics/SVG/1.1/DTD/svg11.dtd\">\n"
				<< "<svg xmlns=\"http://www.w3.org/2000/svg\" xmlns:xlink=\"http://www.w3.org/1999/xlink\">\n"
				<< "	<defs>\n"
				<< "		<style type=\"text/css\">\n"
				<< "		<![CDATA[\n"
				<< "			line, path { stroke: black; }\n"
				<< "			text { font-family: \"Verdana\"; font-size: 11px; }\n"
				<< "			text.legends { font-size: 10px; }\n"
				<< "			.max { stroke: red; }\n"
				<< "			.avg { stroke: green; stroke-dasharray: 3, 2; }\n"
				<< "			.min { stroke: blue; stroke-dasharray: 1, 2; }\n"
				<< "		]]>\n"
				<< "		</style>\n"
				<< "		<g id=\"modules\">\n"
				<< "			<text x=\"0\" y=\"0\">Species: " << modules->at(Module::gene) << "</text>\n"
				<< "			<text x=\"0\" y=\"16\">Fitness: " << modules->at(Module::fitness) << "</text>\n"
				<< "			<text x=\"0\" y=\"32\">Mating: " << modules->at(Module::mating) << "</text>\n"
				<< "			<text x=\"0\" y=\"48\">Mutator: " << modules->at(Module::mutator) << "</text>\n"
				<< "			<text x=\"0\" y=\"64\">Selector: " << modules->at(Module::selector) << "</text>\n"
				<< "		</g>\n"
				<< "		<g id=\"config\">\n"
				<< "			<text x=\"0\" y=\"0\">Individuals: " << config->capacity << "</text>\n"
				<< "			<text x=\"0\" y=\"16\">Generations: " << config->doomsday << "</text>\n"
				<< "			<text x=\"0\" y=\"32\">Mating rate: " << config->mating_rate << "</text>\n"
				<< "			<text x=\"0\" y=\"48\">Mutation rate: " << config->mutation_rate << "</text>\n"
				<< "			<text x=\"0\" y=\"64\">Elitism: " << config->elitism << "</text>\n"
				<< "		</g>\n"
				<< "		<marker id=\"arrow\" viewBox=\"0 0 10 10\" refX=\"0\" refY=\"5\" markerUnits=\"strokeWidth\" markerWidth=\"7\" markerHeight=\"7\" orient=\"auto\">\n"
				<< "			<path d=\"M 0 0 L 10 5 L 0 10 Z\" />\n"
				<< "		</marker> \n"
				<< "		<g id=\"axes\">\n"
				<< "			<path d=\"M 0 240 L 0 0\" style=\"marker-end: url(#arrow);\" />\n"
				<< "			<text class=\"legends\" x=\"5\" y=\"0\">Fitness</text>\n"
				<< "			<path d=\"M 0 240 L 320 240\" style=\"marker-end: url(#arrow);\" />\n"
				<< "			<text class=\"legends\" x=\"320\" y=\"234\">Generation</text>\n"
				<< "		</g>\n"
				<< "		<g id=\"legends\">\n"
				<< "			<line class=\"max\" x1=\"0\" y1=\"0\" x2=\"16\" y2=\"0\" />\n"
				<< "			<text class=\"legends\" x=\"20\" y=\"3\">max</text>\n"
				<< "			<line class=\"avg\" x1=\"0\" y1=\"12\" x2=\"16\" y2=\"12\" />\n"
				<< "			<text class=\"legends\" x=\"20\" y=\"15\">avg</text>\n"
				<< "			<line class=\"min\" x1=\"0\" y1=\"24\" x2=\"16\" y2=\"24\" />\n"
				<< "			<text class=\"legends\" x=\"20\" y=\"27\">min</text>\n"
				<< "		</g>\n"
				<< "	</defs>\n"
				<< "	<use x=\"360\" y=\"16\" xlink:href=\"#modules\" />\n"
				<< "	<use x=\"360\" y=\"128\" xlink:href=\"#config\" />\n"
				<< "	<use x=\"16\" y=\"16\" width=\"320\" height=\"240\" xlink:href=\"#axes\" />\n"
				<< "	<use x=\"300\" y=\"16\" xlink:href=\"#legends\" />\n";

	double generation_scale = 320.0 / config->doomsday;
	this->generation_axis.reserve(config->doomsday + 1);
	this->generation_axis.push_back(this->fitness_margin);
	for (unsigned int i = 0; i < config->doomsday; ++i)
		this->generation_axis.push_back(this->generation_axis[i] + generation_scale);
		// generate ticks on the axes
	this->fitness_margin += this->fitness_scale;
	return true;
}

void Plotter_SVG::plot(unsigned int generation, double min, double avg, double max)
{
	if (generation-- < 2)
	{
		this->avg *= this->fitness_scale;
		this->avg  = this->fitness_margin - avg;
		this->max *= this->fitness_scale;
		this->max  = this->fitness_margin - max;
		this->min *= this->fitness_scale;
		this->min  = this->fitness_margin - min;
		return;
	}
	avg *= this->fitness_scale;
	avg  = this->fitness_margin - avg;
	max *= this->fitness_scale;
	max  = this->fitness_margin - max;
	min *= this->fitness_scale;
	min  = this->fitness_margin - min;
	generation--;
	int prev = generation - 1;
	this->svg	<< "	<line class=\"max\" x1=\"" << this->generation_axis[prev] << "\" y1=\"" << this->max << "\" x2=\"" << this->generation_axis[generation] << "\" y2=\"" << max << "\" />\n"
				<< "	<line class=\"avg\" x1=\"" << this->generation_axis[prev] << "\" y1=\"" << this->avg << "\" x2=\"" << this->generation_axis[generation] << "\" y2=\"" << avg << "\" />\n"
				<< "	<line class=\"min\" x1=\"" << this->generation_axis[prev] << "\" y1=\"" << this->min << "\" x2=\"" << this->generation_axis[generation] << "\" y2=\"" << min << "\" />\n";
	this->avg = avg;
	this->max = max;
	this->min = min;
}
