/************************************************************************************
  Program:		Network Sniffer
  File:			networkmodule.cpp
  Description:	NetworkModule class implementation file.
  Author:		Taryk Tordjman
 ***********************************************************************************/

#include "networkmodule.h"
#include <QLabel>
#include <QTreeWidget>

/************************************************
  Network Device Class
***********************************************/

NetworkDevice::NetworkDevice()
{
}

NetworkDevice::~NetworkDevice()
{
	clearChildren();
}

void NetworkDevice::clearChildren()
{
	if (children.count() > 0)
	{
		for (int i = 0; i < children.count(); i++)
		{
			NetworkDevice *device = children.at(i);
			delete device;
		}

		children.clear();
	}
}

/************************************************
  Network Module Class Constructor/Destructor
***********************************************/

NetworkModule::NetworkModule() :
	Module("Network",
		"Scans your local area network for shared files, folders and networked computers.",
		"Scanning your network...", 2)
{
	network.name = "Entire Network";
	network.icon = ":/Resources/NetworkDomain.png";
}

NetworkModule::~NetworkModule()
{
	network.clearChildren();
}

/************************************************
  Run module method
***********************************************/

void NetworkModule::runModule()
{
	reset();
	sharedDiskExists = false;
	networkComputerCount = 0;
	passed = true;
	showNetworkMap = false;
	network.clearChildren();

	// get the list of network devices
	SSFWNETWORKDEVICE networkDevices;
	ListNetworkDevices(&networkDevices);

	// create our network device map
	for (int i = 0; i < networkDevices.num_children; i++)
		addDeviceToNetworkMap(networkDevices.pChildren[i], &network);

	// check if there are any computers or shared files on the network
	if (network.children.count() == 0 || (networkComputerCount == 0 && !sharedDiskExists))
	{
		result = "No network shares or computers found.";
		details = "Your computer is not currently sharing network drives and "
			"there are no other computers visible on your network.";
		passed = true;
		return;
	}

	result = "Network computers or shares found!";
	showNetworkMap = true;

	if (sharedDiskExists && networkComputerCount > 1)
	{
		details = "There are other computers connected to your network, and "
		"there are shared drives or folders on the network.";
		threatScore = 2;
	}
	else if (sharedDiskExists)
	{
		details = "There are shared drives or folders on your network.";
		threatScore = 1;
	}
	else if (networkComputerCount > 1)
	{
		details = "There are other computers connected to your network.";
		threatScore = 1;
	}

	details += " You should pay close attention to the list of shares and networked computers and "
		"ensure that you recognize all of them.";
	passed = false;
}

/************************************************
  Manage network device map
***********************************************/

void NetworkModule::addDeviceToNetworkMap(LPSSFWNETWORKDEVICE device, NetworkDevice *parent)
{
	if (device == NULL) return;

	if ((device->container) && (device->num_children == 0))
	{
		if (strcmp((device->displayType), "Entire Network") == 0) return;
		if (strcmp((device->displayType), "Network") == 0) return;
		if (strcmp((device->displayType), "Domain") == 0) return;
	}

	NetworkDevice *newDevice = new NetworkDevice;

	if ((device->displayType != NULL) && (device->displayType[0] != 0))
		newDevice->type += device->displayType;

	if ((device->type != NULL) && (device->type[0] != 0))
	{
		if (!newDevice->type.isEmpty())
			newDevice->type += " ";

		newDevice->type += device->type;
	}

   // append the device name
   if ((device->name != NULL) && (device->name[0] != 0))
	   newDevice->name += device->name;

   // append the device comment
   if ((device->comment != NULL) && (device->comment[0] != 0))
   {
	   newDevice->name += " (";
	   newDevice->name += device->comment;
	   newDevice->name += ")";
   }

	if (strcmp((device->type), "Disk Resource") == 0)
		newDevice->icon = ":/Resources/NetworkFolder.png";
	else if (strcmp((device->type), "Print Resource") == 0)
		newDevice->icon = ":/Resources/NetworkPrinter.png";
	else if (strcmp((device->displayType), "Domain") == 0)
		newDevice->icon = ":/Resources/NetworkGroup.png";
	else if (strcmp((device->displayType), "Server") == 0)
		newDevice->icon = ":/Resources/NetworkServer.png";
	else if (strcmp((device->displayType), "File") == 0)
		newDevice->icon = ":/Resources/NetworkFolder.png";
	else
		newDevice->icon = ":/Resources/NetworkDomain.png";

	parent->children.append(newDevice);

	// keep track of whether there are any shared disk/files
	if (strcmp((device->type), "Disk Resource") == 0)
		sharedDiskExists = true;

	// keep track of the number of computers on the network
	if (strcmp((device->displayType), "Server") == 0)
		networkComputerCount++;

	// process children of the device
	if (device->num_children > 0)
	{
		for (int i = 0; i < device->num_children; i++)
			addDeviceToNetworkMap(device->pChildren[i], newDevice);
	}
}

/************************************************
  Manage module view
***********************************************/

void NetworkModule::updateModuleView(ModuleView *view)
{
	// update the module details
	if (!details.isEmpty())
		view->addDetailLabel(details);

	if (showNetworkMap)
	{
		// create the tree widget root item for the network
		QTreeWidgetItem *rootItem = new QTreeWidgetItem();
		rootItem->setText(0, network.name);
		rootItem->setIcon(0, QIcon(network.icon));

		// recursively build the network tree
		for (int i = 0; i < network.children.count(); i++)
			addDeviceTreeItem(network.children.at(i), rootItem);

		// build the tree view
		QTreeWidget *tree = new QTreeWidget();
		tree->setColumnCount(2);
		tree->setColumnWidth(0, 320);
		tree->setHeaderLabels(QStringList() << "Network Resource Name" << "Resource Type" );
		tree->insertTopLevelItem(0, rootItem);
		expandTreeItem(rootItem);

		// add the tree
		view->addDetailWidget(tree);
	}
}

void NetworkModule::addDeviceTreeItem(NetworkDevice *device, QTreeWidgetItem *currentItem)
{
	QTreeWidgetItem *childItem = new QTreeWidgetItem;
	childItem->setText(0, device->name);
	childItem->setText(1, device->type);

	if (device->icon.length() > 0)
		childItem->setIcon(0, QIcon(device->icon));

	childItem->setExpanded(true);
	currentItem->addChild(childItem);

	for (long i = 0; i < (device->children.count()); i++)
		addDeviceTreeItem(device->children.at(i), childItem);
}

void NetworkModule::expandTreeItem(QTreeWidgetItem *item)
{
	item->setExpanded(true);

	for (int i = 0; i < item->childCount(); i++)
		expandTreeItem(item->child(i));
}

/************************************************
  Manage html summary
***********************************************/

void NetworkModule::writeSummary(HtmlWriter *writer)
{
	writer->writePar(result);

	if (!details.isEmpty())
		writer->writePar(details);

	if (showNetworkMap)
	{
		writer->writeHtml("<table border='1'><tr><th>Network Resource Name</th><th>Resource Type</th></tr>\n");
		writeDeviceRow(&network, writer, 0);
		writer->writeHtml("</table>\n");
	}
}

void NetworkModule::writeDeviceRow(NetworkDevice *device, HtmlWriter *writer, int level)
{
	writer->writeHtml("<tr><td>");

	for (int i = 0; i < level; i++)
		writer->writeHtml("&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;");

	writer->writeHtml("&bull; ");
	writer->write(device->name);
	writer->writeHtml("</td><td>");
	writer->write(device->type);
	writer->writeHtml("</td></tr>\n");

	level++;

	for (int i = 0; i < device->children.count(); i++)
		writeDeviceRow(device->children.at(i), writer, level);
}
