/************************************************************************************
  Program:		Network Sniffer
  File:			wirelessadaptermodule.cpp
  Description:	WirelessAdapterModule class implementation file.
  Author:		Taryk Tordjman
 ***********************************************************************************/

#include "wirelessadaptermodule.h"
#include <QTreeWidget>

WirelessAdapterModule::WirelessAdapterModule() :
	Module("Wireless Adapters",
		"Checks the security of any installed wireless adapters.",
		"Scanning your wireless adapters...", 2)
{
}

void WirelessAdapterModule::runModule()
{
	reset();

	accessPoints.ClearAccessPoints();
    GetWirelessNetworkInfo(&accessPoints);

	if (accessPoints.adapter[0] == 0)
	{
		 result = "No wireless adapters found.";
		 passed = true;
		 return;
	}

	if (accessPoints.num_accesspoints == 0)
	{
		result = "No wireless access points found.";
		passed = true;
		return;
	}

	// determine if we are connected to any insecure networks
	NetworkSecurityState leastSecureNetwork = NetworkSecuritySecure;

	for (long i = 0; i < accessPoints.num_accesspoints; i++)
	{
		if (strcmp((accessPoints.authentication[i]), "open") == 0)
		{
			if (leastSecureNetwork > NetworkSecurityOpen)
				leastSecureNetwork = NetworkSecurityOpen;
		}
		 else if (strcmp((accessPoints.authentication[i]), "WEP") == 0)
		{
			if (leastSecureNetwork > NetworkSecurityWEP)
				leastSecureNetwork = NetworkSecurityWEP;
		}
	}

	if (leastSecureNetwork == NetworkSecurityOpen)
	{
		result = "You are connected to an insecure network!";
		details = "Your computer is connected to a network with no encryption. "
			"Using an unencrypted wireless network is dangerous, since anyone within range of the network can listen in on "
			"what you are doing and potentially compromise your security and your personal data. You should consult the user manual that "
			"came with your wireless router to find out how to switch your network to use encryption, such as WPA2 encryption.";
		passed = false;
	}
	else if (leastSecureNetwork == NetworkSecurityWEP)
	{
		result = "You are connected to a potentially insecure network!";
		details = "Your computer is connected to a network with WEP encryption. "
		   "While a network with WEP encryption is better than no encryption, it can take as little as 60 seconds for "
		   "someone within range of the network to break the encryption and potentially listen in on what you are "
		   "doing, possibly compromising your security and your personal data. You should consult the user manual that "
		   "came with your wireless router to find out how to switch your network from WEP encryption to a more secure encryption type, "
		   "such as WPA2.";
		passed = false;
	}
	else
	{
		result = "You are connected to a secure network";
		details = "Your computer is connected to a secure network. The type of encryption you are using is "
		   "extremely difficult for an attacker to break. Continue using this type of encryption on your wireless network to "
		   "help keep your computer secure.";
		passed = true;
	}
}

void WirelessAdapterModule::updateModuleView(ModuleView *view)
{
	if (!details.isEmpty())
		view->addDetailLabel(details);

	if (accessPoints.num_accesspoints > 0)
	{
		QTreeWidget *list = new QTreeWidget();
		list->setColumnCount(3);
		list->setHeaderLabels(QStringList() << "Wireless Access Point" << "Authentication Mode" << "Is Secure" );
		list->setColumnWidth(0, 200);
		list->setColumnWidth(1, 160);
		list->setRootIsDecorated(false);
		view->addDetailWidget(list);

		for (long i = 0; i < accessPoints.num_accesspoints; i++)
		{
			QTreeWidgetItem *item = new QTreeWidgetItem();
			item->setText(0, accessPoints.name[i]);
			item->setText(1, accessPoints.authentication[i]);

			if (strcmp((accessPoints.authentication[i]), "open") == 0)
				item->setText(2, "Not Secure");
			else if (strcmp((accessPoints.authentication[i]), "WEP") == 0)
				item->setText(2, "Not Secure");
			else
				item->setText(2, "Secure");

			list->insertTopLevelItem(i, item);
		}
	}
}

void WirelessAdapterModule::writeSummary(HtmlWriter *writer)
{
	if (!result.isEmpty())
		writer->writePar(result);

	if (!details.isEmpty())
		writer->writePar(details);

	if (accessPoints.num_accesspoints > 0)
	{
		writer->writeHtml("<table border='1'><tr><th>Wireless Access Point</th><th>Authentication Mode</th><th>Is Secure</th></tr>\n");

		for (long i = 0; i < accessPoints.num_accesspoints; i++)
		{
			writer->writeHtml("<tr><td>");
			writer->write(accessPoints.name[i]);
			writer->writeHtml("</td><td>");
			writer->write(accessPoints.authentication[i]);
			writer->writeHtml("</td><td>");

			if (strcmp((accessPoints.authentication[i]), "open") == 0)
				writer->write("Not Secure");
			else if (strcmp((accessPoints.authentication[i]), "WEP") == 0)
				writer->write("Not Secure");
			else
				writer->write("Secure");

			writer->writeHtml("</td></tr>\n");
		}

		writer->writeHtml("</table>\n");
	}
}
