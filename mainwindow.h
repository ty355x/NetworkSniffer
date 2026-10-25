/************************************************************************************
  Program:		Network Sniffer
  File:			mainwindow.h
  Description:	MainWindow class header file.
  Author:		Taryk Tordjman
 ***********************************************************************************/


#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>
#include "mainview.h"
#include "module.h"
#include "summaryview.h"
#include "modulemanager.h"

namespace Ui {
class MainWindow;
}

/**
	The main window for the application
*/
class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    ~MainWindow();

	/** Runs all the modules. */
	void runModules();

	/** Displays the main view. */
	void showMainView();

	/** Displays the scan report summary. */
	void showSummaryView();

	/** Returns the single instance of the main window. */
	static MainWindow *getInstance();

protected:
    MainWindow(QWidget *parent = NULL);
	MainWindow(const MainWindow &);
	MainWindow &operator=(MainWindow &);

private:
	Ui::MainWindow *ui;
	ModuleManager *moduleManager;
	MainView *mainView;
	SummaryView *summaryView;

private slots:
     void on_btnAbout_clicked();

};

#endif // MAINWINDOW_H
