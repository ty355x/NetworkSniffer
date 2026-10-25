#ifndef SSFW_WUPDATE
#define SSFW_WUPDATE

#include <windows.h>
#include <crtdbg.h>
#include <netfw.h>
#include <objbase.h>
#include <oleauto.h>
#include <stdio.h>
#include <wuapi.h>

void DateLastWindowsUpdate(LPSYSTEMTIME pSysTime);

#endif
