/************************************************************************************
  Program:		Network Sniffer
  File:			networkmodule.h
  Description:	NetworkModule class header file.
  Author:		Taryk Tordjman
 ***********************************************************************************/

#ifndef NETWORKMODULE_H
#define NETWORKMODULE_H

#include "../module.h"
#include "../Scans/network.h"
#include <QTreeWidget>
#include <QList>

class NetworkDevice
{
public:
	NetworkDevice();
	~NetworkDevice();
	void clearChildren();
	QString name;
	QString type;
	QString icon;
	QList<NetworkDevice *> children;
};

class NetworkModule : Module
{
public:
    NetworkModule();
	~NetworkModule();
    void runModule();
	void updateModuleView(ModuleView *view);
	void writeSummary(HtmlWriter *writer);
protected:
    void updateView();
private:

	void addDeviceToNetworkMap(LPSSFWNETWORKDEVICE device, NetworkDevice *parent);
	void addDeviceTreeItem(NetworkDevice *device, QTreeWidgetItem *currentItem);
	void writeDeviceRow(NetworkDevice *device, HtmlWriter *writer, int level);
	void expandTreeItem(QTreeWidgetItem *item);

	NetworkDevice network;
	QString details;
	bool sharedDiskExists;
	int networkComputerCount;
	bool showNetworkMap;
};

#endif // NETWORKMODULE_H
