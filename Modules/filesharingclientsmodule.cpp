/************************************************************************************
  Program:		Network Sniffer
  File:			filesharingclientsmodule.cpp
  Description:	FileSharingClientsModule class implementation file.
  Author:		Taryk Tordjman
 ***********************************************************************************/

#include "filesharingclientsmodule.h"
#include <QLabel>
#include <QTreeWidget>

FileSharingClientsModule::FileSharingClientsModule() :
	Module("File Sharing Clients",
		"Scans for file sharing clients that may be installed on your computer.",
		"Scanning for file sharing clients...", 2)
{
}

void FileSharingClientsModule::runModule()
{
	reset();
	p2pPrograms = SSFWP2PLIST();
	ListProgramsP2P(&p2pPrograms);

	if (p2pPrograms.num_p2ps == 0)
	{
		result = "No file sharing software found.";
		details = "No file sharing software was found on your computer. "
			"If you decide to use this type of software in the future, you should use caution and only download "
			"legally obtained software, music and other materials. Using file sharing software "
			"to download or upload copyrighted materials can lead to copyright infringement and "
			"prosecution under antipiracy laws.";
		passed = true;
	}
	else
	{
		result = "File sharing software found!";
		details = "One or more file sharing programs have been found on your computer. "
			"You should use caution and only download legally obtained software, music and other materials. "
			"Using file sharing software to download or upload copyrighted materials can lead to "
			"copyright infringement and prosecution under antipiracy laws.";
		threatScore = 2;
		passed = false;
	}
}

void FileSharingClientsModule::updateModuleView(ModuleView *view)
{
	if (!details.isEmpty())
		view->addDetailLabel(details);

	if (p2pPrograms.num_p2ps > 0)
	{
		// create a tree view to store the file sharing software list
		QTreeWidget *list = new QTreeWidget();
		list->setColumnCount(1);
		list->setHeaderLabels(QStringList() << "File Sharing Client");
		list->setColumnWidth(0, 200);
		list->setRootIsDecorated(false);
		view->addDetailWidget(list);

		// add the file sharing clients to the list
		for (long i = 0; i < (p2pPrograms.num_p2ps); i++)
		{
			QTreeWidgetItem *item = new QTreeWidgetItem();
			item->setText(0, p2pPrograms.name[i]);
			list->insertTopLevelItem(i, item);
		}
	}
}

void FileSharingClientsModule::writeSummary(HtmlWriter *writer)
{
	writer->writePar(result);

	if (!details.isEmpty())
		writer->writePar(details);

	if (p2pPrograms.num_p2ps > 0)
	{
		writer->writeHtml("<table border='1'><tr><th>File Sharing Client</th></tr>\n");

		for (long i = 0; i < (p2pPrograms.num_p2ps); i++)
		{
			writer->writeHtml("<tr><td>");
			writer->write(p2pPrograms.name[i]);
			writer->writeHtml("</tr></td>\n");
		}

		writer->writeHtml("</table>\n");
	}
}
