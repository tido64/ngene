#include "Plotter_SVG.h"

using std::string;
using std::vector;

Plotter_SVG::~Plotter_SVG()
{
	this->svg << "</svg>\n";
	this->svg.close();
	this->generation_axis.clear();
}

bool Plotter_SVG::initiate(string filename, vector<const char *> &modules, const Config &config)
{
	this->svg.open(filename.append(".svg").c_str());
	if (this->svg.is_open())
	{
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
					<< "			<text x=\"0\" y=\"0\">Species: " << modules[gene_module] << "</text>\n"
					<< "			<text x=\"0\" y=\"16\">Fitness: " << modules[fitness_module] << "</text>\n"
					<< "			<text x=\"0\" y=\"32\">Mating: " << modules[mating_module] << "</text>\n"
					<< "			<text x=\"0\" y=\"48\">Mutator: " << modules[mutator_module] << "</text>\n"
					<< "			<text x=\"0\" y=\"64\">Selector: " << modules[selector_module] << "</text>\n"
					<< "		</g>\n"
					<< "		<g id=\"config\">\n"
					<< "			<text x=\"0\" y=\"0\">Individuals: " << config.adult_pool_capacity << "</text>\n"
					<< "			<text x=\"0\" y=\"16\">Generations: " << config.doomsday << "</text>\n"
					<< "			<text x=\"0\" y=\"32\">Mating rate: " << config.mating_rate << "</text>\n"
					<< "			<text x=\"0\" y=\"48\">Mutation rate: " << config.mutation_rate << "</text>\n"
					<< "			<text x=\"0\" y=\"64\">Elitism: " << config.elitism << "</text>\n"
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
		this->fitness_margin = 16;
		this->fitness_scale = 240;

		double generation_scale = 320.0 / config.doomsday;
		this->generation_axis.reserve(config.doomsday + 1);
		this->generation_axis.push_back(this->fitness_margin);
		for (int i = 0; i < config.doomsday; i++)
			this->generation_axis.push_back(this->generation_axis[i] + generation_scale);
			// generate ticks on the axes

		this->fitness_margin += this->fitness_scale;

		return true;
	}
	else
		return false;
}

void Plotter_SVG::plot(const int generation, double min, double avg, double max)
{
	avg = this->fitness_margin - avg * this->fitness_scale;
	max = this->fitness_margin - max * this->fitness_scale;
	min = this->fitness_margin - min * this->fitness_scale;
	if (generation != 0)
	{
		int p = generation - 1;
		this->svg	<< "	<line class=\"max\" x1=\"" << this->generation_axis[p] << "\" y1=\"" << this->max << "\" x2=\"" << this->generation_axis[generation] << "\" y2=\"" << max << "\" />\n"
					<< "	<line class=\"avg\" x1=\"" << this->generation_axis[p] << "\" y1=\"" << this->avg << "\" x2=\"" << this->generation_axis[generation] << "\" y2=\"" << avg << "\" />\n"
					<< "	<line class=\"min\" x1=\"" << this->generation_axis[p] << "\" y1=\"" << this->min << "\" x2=\"" << this->generation_axis[generation] << "\" y2=\"" << min << "\" />\n";
	}
	this->avg = avg;
	this->max = max;
	this->min = min;
}

