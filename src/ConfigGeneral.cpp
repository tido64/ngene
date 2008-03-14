#include "ConfigFrame.h"

using std::string;
using std::stringstream;

ConfigGeneral::ConfigGeneral(wxWindow *parent) : wxPanel(parent)
{
	wxSize size_spin (64, -1);
	this->layout = new wxFlexGridSizer(8, 2, 4, 8);

	this->layout->Add(new wxStaticText(this, -1, wxT("Doomsday:")), -1, wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL);
	this->doomsday = new wxSpinCtrl(this, -1, wxEmptyString, wxDefaultPosition, size_spin, wxSP_ARROW_KEYS, 10, 9999, 100);
	this->layout->Add(this->doomsday);

	this->layout->Add(new wxStaticText(this, -1, wxT("Adult pool capacity:")), -1, wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL);
	this->capacity = new wxSpinCtrl(this, -1, wxEmptyString, wxDefaultPosition, size_spin, wxSP_ARROW_KEYS, 10, 9999, 100);
	this->layout->Add(this->capacity);

	this->layout->Add(new wxStaticText(this, -1, wxT("Lifespan:")), -1, wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL);
	this->lifespan = new wxSpinCtrl(this, -1, wxEmptyString, wxDefaultPosition, size_spin, wxSP_ARROW_KEYS, 1, 100, 1);
	this->layout->Add(this->lifespan);

	this->layout->Add(new wxStaticText(this, -1, wxT("Mating rate:")), -1, wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL);
	this->mating_rate = new wxSpinCtrl(this, -1, wxEmptyString, wxDefaultPosition, size_spin, wxSP_ARROW_KEYS, 1, 100, 90);
	this->layout->Add(this->mating_rate);

	this->layout->Add(new wxStaticText(this, -1, wxT("Offspring rate:")), -1, wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL);
	this->offspring_rate = new wxSpinCtrl(this, -1, wxEmptyString, wxDefaultPosition, size_spin, wxSP_ARROW_KEYS, this->capacity->GetValue(), 9999, this->capacity->GetValue());
	this->layout->Add(this->offspring_rate);

	this->layout->Add(new wxStaticText(this, -1, wxT("Mutation rate:")), -1, wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL);
	this->mutation_rate = new wxSpinCtrl(this, -1, wxEmptyString, wxDefaultPosition, size_spin, wxSP_ARROW_KEYS, 1, 100, 10);
	this->layout->Add(this->mutation_rate);

	this->layout->Add(new wxStaticText(this, -1, wxT("Elitism:")), -1, wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL);
	this->elitism = new wxCheckBox(this, -1, wxEmptyString);
	this->layout->Add(this->elitism, -1, wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL);

	this->layout->Add(new wxStaticText(this, -1, wxT("Max prodigies:")), -1, wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL);
	this->prodigies = new wxSpinCtrl(this, -1, wxEmptyString, wxDefaultPosition, size_spin, wxSP_ARROW_KEYS, 0, 9999, 0);
	this->prodigies->Disable();
	this->layout->Add(this->prodigies);

	this->border = new wxBoxSizer(wxVERTICAL);
	this->border->Add(this->layout, 0, wxEXPAND | wxALL, 5);
	SetSizer(this->border);

	Connect(this->capacity->GetId(), wxEVT_COMMAND_SPINCTRL_UPDATED, wxCommandEventHandler(ConfigGeneral::update_offspring_rate));
	Connect(this->prodigies->GetId(), wxEVT_COMMAND_SPINCTRL_UPDATED, wxCommandEventHandler(ConfigGeneral::update_offspring_rate));
	Connect(this->lifespan->GetId(), wxEVT_COMMAND_SPINCTRL_UPDATED, wxCommandEventHandler(ConfigGeneral::toggle_prodigy));
}

const string ConfigGeneral::configuration()
{
	stringstream c;
	c	<< this->capacity->GetValue() << "\t\t# adult pool capacity\n"
		<< this->doomsday->GetValue() << "\t\t# doomsday\n"
		<< this->elitism->GetValue() << "\t# elitism\n"
		<< this->lifespan->GetValue() << "\t\t# lifespan\n"
		<< this->mating_rate->GetValue() << "\t\t# mating rate\n"
		<< this->prodigies->GetValue() << "\t\t# max prodigies\n"
		<< this->mutation_rate->GetValue() << "\t\t# mutation rate\n"
		<< this->offspring_rate->GetValue() << "\t\t# offspring rate\n";
	return c.str();
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
		this->offspring_rate->SetValue(this->capacity->GetValue() + this->prodigies->GetValue());
}
