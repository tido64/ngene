#include <sstream>
#include <wx/checkbox.h>
#include <wx/panel.h>
#include <wx/sizer.h>
#include <wx/spinctrl.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>

class ConfigGeneral : public wxPanel
{
public:
	ConfigGeneral(wxWindow *parent);
	const std::string configuration();

private:
	wxBoxSizer *border;
	wxCheckBox *elitism;
	wxFlexGridSizer *layout;
	wxSpinCtrl
		*capacity,
		*doomsday,
		*lifespan,
		*mating_rate,
		*prodigies,
		*mutation_rate,
		*offspring_rate;

	void toggle_prodigy(wxCommandEvent &event);
	void update_offspring_rate(wxCommandEvent &event);
};
