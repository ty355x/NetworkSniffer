/************************************************************************
  Program:		Network Sniffer
  File:			mainwindow.cpp
  Description:	MainWindow class implementation file.
  Author:		Taryk Tordjman
 ***********************************************************************/

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "aboutdialog.h"
#include <QFile>
#include <QTextStream>

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow),
	moduleManager(NULL),
	mainView(NULL),
	summaryView(NULL)
{
    ui->setupUi(this);

	setWindowState(Qt::WindowMaximized);

	// setup the layout for the main view pane
    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->setSpacing(0);
    mainLayout->setMargin(0);
	mainLayout->setAlignment(Qt::AlignTop);
    ui->mainPane->setLayout(mainLayout);

	// setup the views and add them to the main pane
	mainView = new MainView;
	summaryView = new SummaryView;
	ui->mainPane->layout()->addWidget(mainView);
	ui->mainPane->layout()->addWidget(summaryView);

	// set up the module manager
	moduleManager = new ModuleManager(mainView, summaryView);

	// show the main view
	showMainView();
}

MainWindow::~MainWindow()
{
	if (moduleManager != NULL)
	{
		delete moduleManager;
		moduleManager = NULL;
	}

	delete ui;
}

MainWindow *MainWindow::getInstance()
{
	static MainWindow instance = MainWindow();
	return &instance;
}

void MainWindow::showMainView()
{
	summaryView->hide();
	mainView->show();
 }

void MainWindow::showSummaryView()
{
	mainView->hide();
	summaryView->show();
}

void MainWindow::runModules()
{
	moduleManager->runModules();
}

void MainWindow::on_btnAbout_clicked()
{
    AboutDialog wndAbout(this);
    wndAbout.exec();
}
