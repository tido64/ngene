#include <wx/app.h>
#include "ConfigFrame.h"

class Configurator : public wxApp
{
public:
	virtual bool OnInit();
};

DECLARE_APP(Configurator);
