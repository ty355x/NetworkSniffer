/************************************************************************
  Program:		Network Sniffer
  File:			module.cpp
  Description:	Module class implementation file.
  Author:		Taryk Tordjman
 ***********************************************************************/

#include "module.h"

#include "Modules/filesharingclientsmodule.h"
#include "Modules/firewallmodule.h"
#include "Modules/networkmodule.h"
#include "Modules/windowsupdatemodule.h"
#include "Modules/wirelessadaptermodule.h"

/*********************************************************************
  module factory
*********************************************************************/

QList<Module*> *ModuleFactory::createModules()
{
	QList<Module *> *modules = new QList<Module *>();
	modules->append((Module*) new NetworkModule);
	modules->append((Module*) new FileSharingClientsModule);
	modules->append((Module*) new FirewallModule);
	modules->append((Module*) new WindowsUpdateModule);
	modules->append((Module*) new WirelessAdapterModule);
    return modules;
}

/*********************************************************************
  module class
*********************************************************************/

Module::Module(const QString &name, const QString &description, const QString &scanLabel, int maxThreatScore) :
	name(name),
	description(description),
	scanLabel(scanLabel),
	threatScore(0),
	maxThreatScore(maxThreatScore),
	result(QString()),
	passed(true)
{
}

Module::~Module()
{
}

void Module::reset()
{
	threatScore = 0;
	result = QString();
	passed = true;
}
