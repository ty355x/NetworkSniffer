/************************************************************************************
  Program:		Network Sniffer
  File:			windowsupdatemodule.h
  Description:	WindowsUpdateModule class header file.
  Author:		Taryk Tordjman
 ***********************************************************************************/

#ifndef WINDOWSUPDATEMODULE_H
#define WINDOWSUPDATEMODULE_H

#include "../module.h"
#include "../Scans/wupdate.h"

class WindowsUpdateModule : Module
{
public:
    WindowsUpdateModule();
    void runModule();
	void updateModuleView(ModuleView *view);
	void writeSummary(HtmlWriter *writer);
protected:
    void updateView();
private:
    SYSTEMTIME lastUpdate;
	QString details;
};

#endif // WINDOWSUPDATEMODULE_H
