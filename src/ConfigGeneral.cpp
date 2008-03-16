#include "ConfigFrame.h"

using std::string;
using std::stringstream;

ConfigGeneral::ConfigGeneral(wxWindow *parent) : wxPanel(parent)
{
	wxSize size_spin (64, -1);
	wxFlexGridSizer *layout = new wxFlexGridSizer(8, 2, 4, 8);
	layout->SetFlexibleDirection(wxHORIZONTAL);

	layout->Add(new wxStaticText(this, -1, wxT("Doomsday:")), 0, wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL);
	this->doomsday = new wxSpinCtrl(this, -1, wxEmptyString, wxDefaultPosition, size_spin, wxSP_ARROW_KEYS, 10, 9999, 100);
	layout->Add(this->doomsday);

	layout->Add(new wxStaticText(this, -1, wxT("Adult pool capacity:")), 0, wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL);
	this->capacity = new wxSpinCtrl(this, -1, wxEmptyString, wxDefaultPosition, size_spin, wxSP_ARROW_KEYS, 10, 9999, 100);
	layout->Add(this->capacity);

	layout->Add(new wxStaticText(this, -1, wxT("Lifespan:")), 0, wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL);
	this->lifespan = new wxSpinCtrl(this, -1, wxEmptyString, wxDefaultPosition, size_spin, wxSP_ARROW_KEYS, 1, 100, 1);
	layout->Add(this->lifespan);

	layout->Add(new wxStaticText(this, -1, wxT("Mating rate:")), 0, wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL);
	this->mating_rate = new wxSpinCtrl(this, -1, wxEmptyString, wxDefaultPosition, size_spin, wxSP_ARROW_KEYS, 1, 100, 90);
	layout->Add(this->mating_rate);

	layout->Add(new wxStaticText(this, -1, wxT("Offspring rate:")), 0, wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL);
	this->offspring_rate = new wxSpinCtrl(this, -1, wxEmptyString, wxDefaultPosition, size_spin, wxSP_ARROW_KEYS, this->capacity->GetValue(), 9999, this->capacity->GetValue());
	layout->Add(this->offspring_rate);

	layout->Add(new wxStaticText(this, -1, wxT("Mutation rate:")), 0, wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL);
	this->mutation_rate = new wxSpinCtrl(this, -1, wxEmptyString, wxDefaultPosition, size_spin, wxSP_ARROW_KEYS, 1, 100, 10);
	layout->Add(this->mutation_rate);

	layout->Add(new wxStaticText(this, -1, wxT("Elitism:")), 0, wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL);
	this->elitism = new wxCheckBox(this, -1, wxEmptyString);
	layout->Add(this->elitism, -1, wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL);

	layout->Add(new wxStaticText(this, -1, wxT("Max prodigies:")), 0, wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL);
	this->prodigies = new wxSpinCtrl(this, -1, wxEmptyString, wxDefaultPosition, size_spin, wxSP_ARROW_KEYS, 0, 9999, 0);
	this->prodigies->Disable();
	layout->Add(this->prodigies);

	wxBoxSizer *border = new wxBoxSizer(wxVERTICAL);
	border->Add(layout, 0, wxEXPAND | wxALL, 5);
	SetSizer(border);

	Connect(this->capacity->GetId(), wxEVT_COMMAND_SPINCTRL_UPDATED, wxCommandEventHandler(ConfigGeneral::update_offspring_rate));
	Connect(this->prodigies->GetId(), wxEVT_COMMAND_SPINCTRL_UPDATED, wxCommandEventHandler(ConfigGeneral::update_offspring_rate));
	Connect(this->lifespan->GetId(), wxEVT_COMMAND_SPINCTRL_UPDATED, wxCommandEventHandler(ConfigGeneral::toggle_prodigy));
}

const char *ConfigGeneral::configuration()
{
	stringstream c;
	c	<< this->capacity->GetValue() << "\t\t# adult pool capacity\n"
		<< this->doomsday->GetValue() << "\t\t# doomsday\n"
		<< this->elitism->GetValue() << "\t\t# elitism\n"
		<< this->lifespan->GetValue() << "\t\t# lifespan\n"
		<< this->mating_rate->GetValue() << "\t\t# mating rate\n"
		<< this->prodigies->GetValue() << "\t\t# max prodigies\n"
		<< this->mutation_rate->GetValue() << "\t\t# mutation rate\n"
		<< this->offspring_rate->GetValue() << "\t\t# offspring rate\n";
	return c.str().c_str();
}

void ConfigGeneral::toggle_prodigy(wxCommandEvent &event)
{
	if (this->lifespan->GetValue() > 1)
	{
		this->prodigies->Enable();
		this->prodigies->SetValue(this->capacity->GetValue() / 2);
		update_offspring_rate(event);
	}
	else
	{
		this->prodigies->Disable();
		this->prodigies->SetValue(0);
	}
}

void ConfigGeneral::update_offspring_rate(wxCommandEvent &event)
{
	if (this->offspring_rate->GetValue() < this->capacity->GetValue() + this->prodigies->GetValue())
		this->offspring_rate->SetMin(this->capacity->GetValue() + this->prodigies->GetValue());
}
