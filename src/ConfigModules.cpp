#include "ConfigModules.h"

using std::string;
using std::stringstream;

ConfigModules::ConfigModules(wxWindow *parent)
: wxPanel(parent), modules(Module::number_of_types, 0), module_parameters(Module::number_of_types, 0)
{
	wxFlexGridSizer *layout = new wxFlexGridSizer(8, 2, 4, 8);
	layout->SetFlexibleDirection(wxHORIZONTAL);
	layout->Add(new wxStaticText(this, -1, wxT("Module")), 0, wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL);
	layout->Add(new wxStaticText(this, -1, wxT("Parameter(s)")), 0, wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL);

	find_modules();
	for (int i = 0; i < Module::number_of_types; i++)
	{
		layout->Add(this->modules[static_cast<Module::Type>(i)]);
		layout->Add(this->module_parameters[static_cast<Module::Type>(i)]);
	}

	// filler
	layout->Add(new wxStaticText(this, -1, wxEmptyString), 0);
	layout->Add(new wxStaticText(this, -1, wxEmptyString), 0);
	layout->Add(new wxStaticText(this, -1, wxEmptyString), 0);

	wxBoxSizer *border = new wxBoxSizer(wxVERTICAL);
	border->Add(layout, 0, wxEXPAND | wxALL, 5);
	SetSizer(border);
}

const string ConfigModules::configuration()
{
	stringstream m;
	m	<< "# gene module\n"
		<< this->modules[Module::gene]->GetStringSelection().ToAscii() << '\n'
		<< this->module_parameters[Module::gene]->GetValue().ToAscii() << '\n'
		<< '\n'
		<< "# fitness module\n"
		<< this->modules[Module::fitness]->GetStringSelection().ToAscii() << '\n'
		<< this->module_parameters[Module::fitness]->GetValue().ToAscii() << '\n'
		<< '\n'
		<< "# mating module\n"
		<< this->modules[Module::mating]->GetStringSelection().ToAscii() << '\n'
		<< this->module_parameters[Module::mating]->GetValue().ToAscii() << '\n'
		<< '\n'
		<< "# mutator module\n"
		<< this->modules[Module::mutator]->GetStringSelection().ToAscii() << '\n'
		<< this->module_parameters[Module::mutator]->GetValue().ToAscii() << '\n'
		<< '\n'
		<< "# selector module\n"
		<< this->modules[Module::selector]->GetStringSelection().ToAscii() << '\n'
		<< this->module_parameters[Module::selector]->GetValue().ToAscii() << '\n';
	return m.str().c_str();
}

void ConfigModules::find_modules()
{
	wxArrayString so;
	so.Add(wxT("<description>"));
	so.Add(wxT("module.dll"));
	so.Add(wxT("module2.dll"));
	for (int i = 0; i < Module::number_of_types; i++)
	{
		this->modules[static_cast<Module::Type>(i)] = new wxChoice(this, -1, wxDefaultPosition, wxDefaultSize, so);
		this->modules[static_cast<Module::Type>(i)]->SetSelection(0);
		this->module_parameters[static_cast<Module::Type>(i)] = new wxTextCtrl(this, -1, wxT("none"));
	}
}
