/************************************************************************************
  Program:		Network Sniffer
  File:			filesharingclientsmodule.h
  Description:	FileSharingClientsModule class header file.
  Author:		Taryk Tordjman
 ***********************************************************************************/

#ifndef FILESHARINGMODULE_H
#define FILESHARINGMODULE_H

#include "../module.h"
#include "../Scans/p2p.h"

class FileSharingClientsModule : public Module
{
public:
    FileSharingClientsModule();
	void runModule();
	void updateModuleView(ModuleView *view);
	void writeSummary(HtmlWriter *writer);

protected:
    void updateView();

private:
    SSFWP2PLIST p2pPrograms;
	QString details;
};

#endif // FILESHARINGMODULE_H
