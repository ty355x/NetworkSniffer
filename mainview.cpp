/************************************************************************
  Program:		Network Sniffer
  File:			mainview.cpp
  Description:	MainView class implementation file.
  Author:		Taryk Tordjman
 ***********************************************************************/

#include "mainview.h"
#include "ui_mainview.h"
#include "mainwindow.h"

MainView::MainView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainView)
{
    ui->setupUi(this);

    QVBoxLayout *vLayout = new QVBoxLayout;
    vLayout->setAlignment(Qt::AlignTop);
    vLayout->setMargin(0);
	vLayout->setSpacing(2);
    ui->modulesPane->setLayout(vLayout);

	ui->lblThreatScore->hide();
	ui->paneScanning->hide();
	ui->btnViewReport->hide();
}

MainView::~MainView()
{
	delete ui;
}

void MainView::addModuleView(ModuleView *view)
{
	ui->modulesPane->layout()->addWidget(view);
}

void MainView::setProgressStatus(const QString &text)
{
    ui->lblScanProgress->setText(text);
}

void MainView::setStatus(const QString &text)
{
    ui->lblStatus->setText(text);
}

void MainView::scanComplete(int threatScore, int maxThreatScore)
{
	// show the status pane
	ui->paneScanning->hide();
	ui->paneStatus->show();

	// show the report button
	ui->btnViewReport->show();

	// display the threat score
	ui->lblThreatScore->setText(QString("Your threat score is: %1/%2.").arg(
		threatScore).arg(maxThreatScore));
	ui->lblThreatScore->show();

	// update labels
	ui->lblStatusTitle->setText("Scan complete");
	ui->lblStatus->setText("Click <strong><em>Run Scans</em></strong> to scan your computer again. Or click "
		"<strong><em>View Scan Report</em></strong> to view a printable report of your most recent scan.");
}

void MainView::on_btnRunModules_clicked()
{
	setProgressStatus("Preparing to scan...");
	ui->paneStatus->hide();
	ui->paneScanning->show();
	ui->btnViewReport->hide();
	MainWindow::getInstance()->runModules();
}

void MainView::on_btnViewReport_clicked()
{
	MainWindow::getInstance()->showSummaryView();
}
