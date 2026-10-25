/************************************************************************************
  Program:		Network Sniffer
  File:			firewallmodule.cpp
  Description:	FirewallModule class implementation file.
  Author:		Taryk Tordjman
 ***********************************************************************************/

#include "firewallmodule.h"
#include "../Scans/firewall.h"

FirewallModule::FirewallModule() :
	Module("Firewall",
		"Checks that a firewall is protecting your computer.",
		"Scanning your firewall...", 2)
{
}

void FirewallModule::runModule()
{
	reset();
	passed = CheckFirewallEnabled();

	if (passed)
	{
	   result = "Firewall Enabled.";
	   details = "A firewall is enabled on this machine and is helping to protect you against attacks.";
	}
	else
	{
	   result = "Windows Firewall is disabled, and no third-party Firewall was detected.";
	   details = "No active firewall was found on this machine. You should turn on the Windows Firewall or "
		"enable your third-party firewall as soon as possible so that your machine is better protected against threats.";
	   threatScore = 2;
	}
}

void FirewallModule::updateModuleView(ModuleView *view)
{
	if (!details.isEmpty())
		view->addDetailLabel(details);
}

void FirewallModule::writeSummary(HtmlWriter *writer)
{
	writer->writePar(result);

	if (!details.isEmpty())
		writer->writePar(details);
}
