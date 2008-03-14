#include <wx/filedlg.h>
#include <wx/frame.h>
#include <wx/menu.h>
#include <wx/notebook.h>

#include "ConfigGeneral.h"
#include "ConfigModules.h"

class ConfigFrame : public wxFrame
{
public:
	ConfigFrame();
	~ConfigFrame();

	/// Processes menu File|Open
	void OnMenuFileOpen(wxCommandEvent &event);

	/// Processes menu File|Save
	void OnMenuFileSaveAs(wxCommandEvent &event);

	/// Processes menu File|Quit
	void OnMenuFileQuit(wxCommandEvent &event);

protected:
	DECLARE_EVENT_TABLE()

private:
	ConfigGeneral *general;
	wxBoxSizer *sizer;
	wxMenu *filemenu;
	wxMenuBar *menubar;
	wxNotebook *notebook;
};
