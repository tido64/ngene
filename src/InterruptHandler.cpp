#include "InterruptHandler.h"

bool TERMINATION_PENDING = false;
const char *INTMSG = "\rUser aborted! Stand by for termination\n";

InterruptHandler::InterruptHandler()
{
#ifdef WIN32
	if(!SetConsoleCtrlHandler((PHANDLER_ROUTINE)int_handle, true))
		printf("==> Failed to register control handler\n");
#else
	if(signal(SIGINT, SIG_IGN) != SIG_IGN)
		signal(SIGINT, int_handle);
#endif
}

#ifdef WIN32
BOOL int_handle(DWORD fdwCtrlType)
{
	TERMINATION_PENDING = true;
	switch (fdwCtrlType)
	{
		case CTRL_C_EVENT:
			printf("%s", INTMSG);
			return TRUE;
		case CTRL_CLOSE_EVENT:
			printf("%s", INTMSG);
			return TRUE;
		default:
			return FALSE;
	}
}

#else
void int_handle(int sig)
{
	TERMINATION_PENDING = true;
	printf("%s", INTMSG);
}

#endif
