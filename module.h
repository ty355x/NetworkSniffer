/************************************************************************************
  Program:		Network Sniffer
  File:			module.h
  Description:	Module class header file.
  Author:		Taryk Tordjman
 ***********************************************************************************/

#ifndef MODULE_H
#define MODULE_H

#include <QList>
#include <QWidget>
#include "moduleview.h"
#include "htmlwriter.h"

/**
	The base class for module components.
	Modules implement a runModule method which performs a module-specific task.
*/
class Module
{
public:
	Module(const QString &name, const QString &description, const QString &scanLabel, int maxThreatScore);
    ~Module();

	/** Runs the module. */
    virtual void runModule() = 0;

	/** Updates the module view gui. */
	virtual void updateModuleView(ModuleView *view) = 0;

	/** Writes a scan summary to the html log file document. */
	virtual void writeSummary(HtmlWriter *writer) = 0;

	/** Returns the name of the module. */
	QString& getName() { return name; }

	/** Returns a description of the module. */
	QString& getDescription() { return description; }

	/** Returns the text to display when the module is scanning. */
	QString& getScanLabel() { return scanLabel; }

	/** Returns the text to display as the result of a scan. */
	QString& getScanResult() { return result; }

	/** Returns the threat score. */
	int getThreatScore() const { return threatScore; }

	/** Returns the max threat score. */
	int getMaxThreatScore() const { return maxThreatScore; }

	/** Returns true if the module has executed and all scans have passed. */
	bool hasPassed() { return passed; }

protected:
	/** Resets the module to its default state. */
	virtual void reset();

	QString name;
	QString description;
	QString scanLabel;
	QString result;
	int threatScore;
	int maxThreatScore;
	bool passed;
};

/** Factory class that creates all the modules. */
class ModuleFactory
{
public:
	/** Creates the modules and returns them in a list. */
	static QList<Module*>* createModules();
};

#endif // MODULE_H
