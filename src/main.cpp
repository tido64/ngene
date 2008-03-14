#include "main.h"

IMPLEMENT_APP(Configurator);
bool Configurator::OnInit()
{
	ConfigFrame *frame = new ConfigFrame();
	frame->Show(true);
	SetTopWindow(frame);
	return true;
}
