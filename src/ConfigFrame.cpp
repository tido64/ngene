#include "ConfigFrame.h"

ConfigFrame::ConfigFrame()
: wxFrame(static_cast<wxFrame *>(0), -1, wxT("Ngene Configurator"), wxDefaultPosition, wxDefaultSize,
	wxMINIMIZE_BOX | wxSYSTEM_MENU | wxCAPTION | wxCLOSE_BOX)
{
	wxToolBar *toolbar = CreateToolBar(wxTB_HORZ_TEXT | wxTB_NODIVIDER | wxTB_FLAT);
	toolbar->AddTool(wxID_OPEN, wxT("&Open"), wxNullBitmap, wxT("Open existing configuration"));
	toolbar->AddTool(wxID_SAVE, wxT("&Save"), wxNullBitmap, wxT("Save current configuration"));
	toolbar->AddTool(wxID_SAVEAS, wxT("Save &as"), wxNullBitmap, wxT("Save current configuration to a new file"));
	toolbar->AddTool(wxID_EXIT, wxT("E&xit"), wxNullBitmap);
	toolbar->Realize();

	CreateStatusBar(1, 0);

	wxBoxSizer *sizer = new wxBoxSizer(wxHORIZONTAL);
	this->general = new ConfigGeneral(this);
	sizer->Add(this->general);
	sizer->Add(new wxStaticLine(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_VERTICAL));
	this->modules = new ConfigModules(this);
	sizer->Add(this->modules);
	SetSizer(sizer);
	sizer->Fit(this);
	Centre();
}

ConfigFrame::~ConfigFrame() { }

BEGIN_EVENT_TABLE(ConfigFrame, wxFrame)
	EVT_MENU(wxID_OPEN, ConfigFrame::OnMenuFileOpen)
	EVT_MENU(wxID_SAVE, ConfigFrame::OnMenuFileSave)
	EVT_MENU(wxID_SAVEAS, ConfigFrame::OnMenuFileSaveAs)
	EVT_MENU(wxID_EXIT, ConfigFrame::OnMenuFileQuit)
END_EVENT_TABLE()

void ConfigFrame::OnMenuFileOpen(wxCommandEvent &event)
{
	wxFileDialog *dialog = new wxFileDialog(this, _("Open configuration file"), wxT("."), wxEmptyString, _("Configuration files (*.conf)|*.conf"), wxFD_OPEN);
	if (dialog->ShowModal() == wxID_OK)
	{
		this->curr_conf = dialog->GetPath().ToAscii();
		SetStatusText(wxT("Opened ") + wxString::FromAscii(this->curr_conf.c_str()));
	}
	dialog->Close();
}

void ConfigFrame::OnMenuFileSave(wxCommandEvent &event)
{
	ConfigIO::write(this->curr_conf.c_str(), this->general->configuration(), this->modules->configuration());
	SetStatusText(wxT("Saved to ") + wxString::FromAscii(this->curr_conf.c_str()));
}

void ConfigFrame::OnMenuFileSaveAs(wxCommandEvent &event)
{
	wxFileDialog *dialog = new wxFileDialog(this, _("Save configuration as"), wxT("."), wxEmptyString, _("Configuration files (*.conf)|*.conf"), wxFD_SAVE);
	if (dialog->ShowModal() == wxID_OK)
	{
		this->curr_conf = dialog->GetPath().ToAscii();
		OnMenuFileSave(event);
	}
	dialog->Close();
}

void ConfigFrame::OnMenuFileQuit(wxCommandEvent &event)
{
	Close(false);
}
