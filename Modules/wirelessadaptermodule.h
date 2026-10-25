/************************************************************************************
  Program:		Network Sniffer
  File:			wirelessadaptermodule.h
  Description:	WirelessAdapterModule class header file.
  Author:		Taryk Tordjman
 ***********************************************************************************/

#ifndef WIRELESSMODULE_H
#define WIRELESSMODULE_H

#include "../module.h"
#include "../Scans/wireless.h"

class WirelessAdapterModule : Module
{
public:
    WirelessAdapterModule();
    void runModule();
	void updateModuleView(ModuleView *view);
	void writeSummary(HtmlWriter *writer);
protected:
    void updateView();
private:
    SSFWACCESSPOINTLIST accessPoints;
	QString details;

	enum NetworkSecurityState { NetworkSecurityOpen, NetworkSecurityWEP, NetworkSecuritySecure };
};

#endif // WIRELESSMODULE_H
