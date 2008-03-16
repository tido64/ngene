#include <vector>
#include <wx/arrstr.h>
#include <wx/choice.h>
#include <wx/panel.h>
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include "ModuleType.h"

class ConfigModules : public wxPanel
{
public:
	ConfigModules(wxWindow *parent);
	const char *configuration();

private:
	std::vector<wxChoice *> modules;
	std::vector<wxTextCtrl *> module_parameters;

	void find_modules();
};
