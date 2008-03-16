#include <wx/filedlg.h>
#include <wx/frame.h>
#include <wx/statline.h>
#include <wx/toolbar.h>

#include "ConfigGeneral.h"
#include "ConfigIO.h"
#include "ConfigModules.h"

class ConfigFrame : public wxFrame
{
public:
	ConfigFrame();
	~ConfigFrame();

	/// Processes menu File|Open
	void OnMenuFileOpen(wxCommandEvent &event);

	/// Processes menu File|Save
	void OnMenuFileSave(wxCommandEvent &event);

	/// Processes menu File|Save as
	void OnMenuFileSaveAs(wxCommandEvent &event);

	/// Processes menu File|Quit
	void OnMenuFileQuit(wxCommandEvent &event);

protected:
	DECLARE_EVENT_TABLE()

private:
	ConfigGeneral *general;
	ConfigModules *modules;
	std::string curr_conf;
};
