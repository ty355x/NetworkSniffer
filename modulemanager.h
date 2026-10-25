/************************************************************************************
  Program:		Network Sniffer
  File:			modulemanager.h
  Description:	ModuleManager class header file.
  Author:		Taryk Tordjman
 ***********************************************************************************/

#ifndef MODULEMANAGER_H
#define MODULEMANAGER_H

#include <QVector>
#include <QThread>
#include "module.h"
#include "moduleview.h"
#include "mainview.h"
#include "summaryview.h"

/**	Manages the list of modules. */
class ModuleManager : public QThread
{
    Q_OBJECT

public:
	ModuleManager(MainView *mainView, SummaryView *summaryView);
	~ModuleManager();

	/** Runs the modules in a worker thread. */
	void runModules();

protected:
	void run();

private:
	QList<Module*> *modules;
	QList<ModuleView*> moduleViews;

	MainView *mainView;
	SummaryView *summaryView;

private slots:
	void setModuleViewStatusScanning(int moduleIndex);
	void updateView(int moduleIndex);
	void onRunComplete();
};

#endif // MODULEMANAGER_H
