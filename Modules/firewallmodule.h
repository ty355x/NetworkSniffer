/************************************************************************************
  Program:		Network Sniffer
  File:			firewallmodule.h
  Description:	FirewallModule class header file.
  Author:		Taryk Tordjman
 ***********************************************************************************/

#ifndef FIREWALLMODULE_H
#define FIREWALLMODULE_H

#include "../module.h"

class FirewallModule : public Module
{

public:
    FirewallModule();
    void runModule();
	void updateModuleView(ModuleView *view);
	void writeSummary(HtmlWriter *writer);

protected:
    void updateView();

private:
     bool firewallEnabled;
	 QString details;
};

#endif // FIREWALLMODULE_H
