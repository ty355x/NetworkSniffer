/************************************************************************************
  Program:		Network Sniffer
  File:			mainview.h
  Description:	MainView class header file.
  Author:		Taryk Tordjman
 ***********************************************************************************/

#ifndef MAINVIEW_H
#define MAINVIEW_H

#include <QWidget>
#include "moduleview.h"

namespace Ui {
class MainView;
}

/**	The main view pane for the application. */
class MainView : public QWidget
{
    Q_OBJECT
    
public:
    explicit MainView(QWidget *parent = 0);
    ~MainView();

	/** Adds a module view widget to the list of modules. */
	void addModuleView(ModuleView *view);

	/** Sets the text displayed in the status label. */
	void setStatus(const QString &text);

public slots:

	/** Sets the text displayed in the progress status label. */
	void setProgressStatus(const QString &text);

	/** Should be called after all the modules have been executed. */
	void scanComplete(int threatScore, int maxThreatScore);

private slots:
    void on_btnRunModules_clicked();
	void on_btnViewReport_clicked();

private:
    Ui::MainView *ui;
};

#endif // MAINVIEW_H
