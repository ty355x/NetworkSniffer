/************************************************************************************
  Program:		Network Sniffer
  File:			windowsupdatemodule.cpp
  Description:	WindowsUpdateModule class implementation file.
  Author:		Taryk Tordjman
 ***********************************************************************************/

#include "windowsupdatemodule.h"

WindowsUpdateModule::WindowsUpdateModule() :
	Module("Windows Update",
		"Checks the last time that windows update was executed.",
		"Scanning windows update...", 2)
{
}

void WindowsUpdateModule::runModule()
{
	reset();

	DateLastWindowsUpdate(&lastUpdate);

	SYSTEMTIME currentTime;
	GetLocalTime(&currentTime);

	char buffer[16384] = {0};
	char buffer2[512] = {0};

	if (lastUpdate.wYear == 0)
	{
		result = "Windows Updates have never been installed!";
		details = "Your operating system is not up to date, and you should run Windows Update immediately. "
			"This will ensure that your computer has the latest patches and updates from Microsoft. We recommend "
			"that you back up your files before running this update to ensure that you do not lose any files in case an "
			"error occurs.";
		threatScore = 2;
		passed = false;
	}
	else if ((((DWORD(currentTime.wYear) * 365) + (DWORD(currentTime.wMonth) * 31) + (DWORD(currentTime.wDay))) - 32) <
		((DWORD(lastUpdate.wYear) * 365) + (DWORD(lastUpdate.wMonth) * 31) + (DWORD(lastUpdate.wDay))))
	{
		strncpy_s(buffer, 16383, "Windows Updates were last installed on ", 39);
		_ltoa_s(long(lastUpdate.wMonth), buffer2, 511, 10);
		strcat_s(buffer, 16383, buffer2);
		strncat_s(buffer, 16383, "/", 1);
		ZeroMemory(buffer2, 512);
		_ltoa_s(long(lastUpdate.wDay), buffer2, 511, 10);
		strcat_s(buffer, 16383, buffer2);
		strncat_s(buffer, 16383, "/", 1);
		ZeroMemory(buffer2, 512);
		_ltoa_s(long(lastUpdate.wYear), buffer2, 511, 10);
		strcat_s(buffer, 16383, buffer2);
		strcat_s(buffer, 16383, " and your computer is up to date.");

		result = buffer;
		details = "Your computer has been updated within the last 30 days. You should continue to "
			"run Windows Update on a regular basis to ensure that your computer is protected and patched.";
		passed = true;
	}
	else
	{
		strncpy_s(buffer, 16383, "Windows Updates have not been installed since ", 46);
		_ltoa_s(long(lastUpdate.wMonth), buffer2, 511, 10);
		strcat_s(buffer, 16383, buffer2);
		strncat_s(buffer, 16383, "/", 1);
		ZeroMemory(buffer2, 512);
		_ltoa_s(long(lastUpdate.wDay), buffer2, 511, 10);
		strcat_s(buffer, 16383, buffer2);
		strncat_s(buffer, 16383, "/", 1);
		ZeroMemory(buffer2, 512);
		_ltoa_s(long(lastUpdate.wYear), buffer2, 511, 10);
		strcat_s(buffer, 16383, buffer2);
		strcat_s(buffer, 16383, " and may NOT be up to date!");

		result = buffer;
		details = "Your computer has not been updated within the last 30 days and may not be "
			"up to date.  You should run Windows Update immediately. This will ensure that your computer has the latest patches "
			"and updates from Microsoft. We recommend that you back up your files before running this update to ensure that you do "
			"not lose any files in case an error occurs.";
		threatScore = 2;
		passed = false;
	}
}

void WindowsUpdateModule::updateModuleView(ModuleView *view)
{
	if (!details.isEmpty())
		view->addDetailLabel(details);
}

void WindowsUpdateModule::writeSummary(HtmlWriter *writer)
{
	writer->writePar(result);
	writer->writePar(details);
}
