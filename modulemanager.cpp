/************************************************************************
  Program:		Network Sniffer
  File:			modulemanager.cpp
  Description:	ModuleManager class implementation file.
  Author:		Taryk Tordjman
 ***********************************************************************/

#include "modulemanager.h"
#include "mainwindow.h"
#include "htmlwriter.h"
#include "windows.h"

#include <QDateTime>

ModuleManager::ModuleManager(MainView *mainView, SummaryView *summaryView) :
	modules(NULL),
	mainView(mainView),
	summaryView(summaryView)
{
	// create the modules
	modules = ModuleFactory::createModules();

	// create a view for each module and add it to the main view
	for (int i = 0; i < modules->count(); i++)
	{
		Module *m = modules->at(i);
		ModuleView *view = new ModuleView(m->getName(), m->getDescription());
		moduleViews.append(view);
		mainView->addModuleView(view);
	}
}

ModuleManager::~ModuleManager()
{	
	// delete the module views
	if (moduleViews.count() > 0)
	{
		for (int i = 0; i < moduleViews.count(); i++)
		{
			ModuleView *view = moduleViews.at(i);
			delete view;
		}
	}

	// delete the modules
	if (modules != NULL)
	{
		for (int i = 0; i < modules->count(); i++)
		{
			Module *m = modules->at(i);
			delete m;
		}

		delete modules;
	}
}

void ModuleManager::runModules()
{
	// make sure we are viewing the main view
	MainWindow::getInstance()->showMainView();

	// clear the summary view
	summaryView->clearHtml();

	// initialize the module views
	for (int i = 0; i < moduleViews.count(); i++)
		moduleViews.at(i)->beforeRun();

	// start the worker thread
    start();
}

// This is run from a worker thread, so any calls to update the gui must be
// invoked.
void ModuleManager::run()
{
	// initialize com for this thread
	CoInitializeEx(0, COINIT_APARTMENTTHREADED);

	for (int i = 0; i < modules->count(); i++)
    {
		// if (i == 1) continue;

		// get the current module
		Module *m = modules->at(i);

		// update the progress label on the main view
		QMetaObject::invokeMethod(mainView, "setProgressStatus",
            Q_ARG(const QString&, m->getScanLabel()));

		// update the module view status to 'scanning'
		QMetaObject::invokeMethod(this, "setModuleViewStatusScanning", Q_ARG(int, i));

		// run the module
        m->runModule();

		// update the view for the module
		QMetaObject::invokeMethod(this, "updateView", Q_ARG(int, i));
    }

	// uninitialize com
	CoUninitialize();

	// invoke the onRunComplete method
	QMetaObject::invokeMethod(this, "onRunComplete");
}

void ModuleManager::setModuleViewStatusScanning(int moduleIndex)
{
	if (moduleIndex < modules->count())
	{
		QString scanLabel = modules->at(moduleIndex)->getScanLabel();
		moduleViews.at(moduleIndex)->setStatusNormal(scanLabel);
	}
}

void ModuleManager::updateView(int moduleIndex)
{
	if (moduleIndex >= modules->count())
		return;

	Module *mod = modules->at(moduleIndex);
	ModuleView *view = moduleViews.at(moduleIndex);

	if (mod->hasPassed())
		view->setStatusPassed(mod->getScanResult());
	else
		view->setStatusFailed(mod->getScanResult());

	mod->updateModuleView(view);
	view->setThreatScore(mod->getThreatScore());
}

void ModuleManager::onRunComplete()
{
	int threatScore = 0;
	int maxThreatScore = 0;

	// calculate the threat score and max score
	for (int i = 0; i < modules->count(); i++)
	{
		Module *m = modules->at(i);
		threatScore += m->getThreatScore();
		maxThreatScore += m->getMaxThreatScore();
	}

	// update the main view
	mainView->scanComplete(threatScore, maxThreatScore);

	// create the html summary
	HtmlWriter writer;
	writer.writeHeader("Network Sniffer Scan Report");
	writer.writePar("Report generated on: " + QDateTime::currentDateTime().toString() + ".");
	writer.writeHtml(QString("<p><strong>Your threat score is: %1/%2.</strong></p>\n").arg(
		threatScore).arg(maxThreatScore));

	for (int i = 0; i < modules->count(); i++)
	{
		Module *m = modules->at(i);
		writer.writeHeader(m->getName());
		writer.writePar(QString("Threat score: %1.").arg(m->getThreatScore()));
		m->writeSummary(&writer);
	}

	writer.endDoc();
	summaryView->setHtml(writer.getHtml());
}
