#include "ConfigFrame.h"

ConfigFrame::ConfigFrame()
: wxFrame(static_cast<wxFrame *>(0), -1, wxT("Ngene Configurator"), wxDefaultPosition, wxSize(240, 320),
	wxMINIMIZE_BOX | wxSYSTEM_MENU | wxCAPTION | wxCLOSE_BOX)
{
	this->menubar = new wxMenuBar();
	this->filemenu = new wxMenu();
	this->filemenu->Append(wxID_OPEN, wxT("&Open..."), wxT("Open existing configuration"));
	this->filemenu->Append(wxID_SAVE, wxT("&Save"), wxT("Save current configuration"));
	this->filemenu->Append(wxID_SAVEAS, wxT("&Save as..."), wxT("Save current configuration to a new file"));
	this->filemenu->AppendSeparator();
	this->filemenu->Append(wxID_EXIT, wxT("&Quit"));
	this->menubar->Append(this->filemenu, wxT("&File"));
	SetMenuBar(this->menubar);

	this->notebook = new wxNotebook(this, -1);
	this->notebook->AddPage(new ConfigGeneral(this), wxT("General"));
	this->notebook->AddPage(new ConfigModules(this), wxT("Modules"));

	this->sizer = new wxBoxSizer(wxVERTICAL);
	this->sizer->Add(this->notebook, -1, wxEXPAND | wxALL, 0);
	SetSizer(this->sizer);

	CreateStatusBar(1, 0);
	SetStatusText(wxT("Ready"));

	Centre();
}

ConfigFrame::~ConfigFrame() { }

BEGIN_EVENT_TABLE(ConfigFrame, wxFrame)
	EVT_MENU(wxID_OPEN, ConfigFrame::OnMenuFileOpen)
	EVT_MENU(wxID_SAVEAS, ConfigFrame::OnMenuFileSaveAs)
	EVT_MENU(wxID_EXIT, ConfigFrame::OnMenuFileQuit)
END_EVENT_TABLE()

void ConfigFrame::OnMenuFileOpen(wxCommandEvent &event)
{
	wxFileDialog *dialog = new wxFileDialog(this, _("Open configuration file"), wxT("."), wxEmptyString, _("Configuration files (*.conf)|*.conf"), wxOPEN);
	if (dialog->ShowModal() == wxID_OK)
	{
		// code here
	}
	dialog->Close();
}

void ConfigFrame::OnMenuFileSaveAs(wxCommandEvent &event)
{
	wxFileDialog *dialog = new wxFileDialog(this, _("Save configuration as"), wxT("."), wxEmptyString, _("Configuration files (*.conf)|*.conf"), wxSAVE);
	if (dialog->ShowModal() == wxID_OK)
	{
		// code here
	}
	dialog->Close();
}

void ConfigFrame::OnMenuFileQuit(wxCommandEvent &event)
{
	Close(false);
}
