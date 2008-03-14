#include "ConfigModules.h"

ConfigModules::ConfigModules(wxWindow *parent)
: wxPanel(parent), modules(Module::number_of_types, 0), module_parameters(Module::number_of_types, 0)
{
	this->layout = new wxFlexGridSizer(6, 2, 4, 8);
	this->layout->Add(new wxStaticText(this, -1, wxT("Module")));
	this->layout->Add(new wxStaticText(this, -1, wxT("Parameter(s)")));

	find_modules();
	for (int i = 0; i < Module::number_of_types; i++)
	{
		this->layout->Add(this->modules[static_cast<Module::Type>(i)]);
		this->layout->Add(this->module_parameters[static_cast<Module::Type>(i)]);
	}

	this->border = new wxBoxSizer(wxVERTICAL);
	this->border->Add(this->layout, 0, wxEXPAND | wxALL, 5);
	SetSizer(this->border);
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
