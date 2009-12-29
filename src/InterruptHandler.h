#ifdef WIN32

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

BOOL int_handle(DWORD);

#else

#include <csignal>

void int_handle(int);

#endif

/// Handles user interruptions such as CTRL+C, user closing the window, etc.
/// that may result in unclean terminations, leaving memories and resources
/// unreleased.

#include <cstdio>

extern bool TERMINATION_PENDING;

class InterruptHandler
{
public:
	InterruptHandler();
};
