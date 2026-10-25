/************************************************************************************
  Program:		Network Sniffer
  File:			moduleview.cpp
  Description:	ModuleView class implementation file.
  Author:		Taryk Tordjman
 ***********************************************************************************/

#include "moduleview.h"
#include "ui_moduleview.h"

// initialize constants

QIcon ModuleView::expandIcon;
QIcon ModuleView::collapseIcon;

const char ModuleView::contentPaneStyle[] =
	"#paneTitle { margin: 1px; padding: 4px; border-top-left-radius: 6px; border-top-right-radius: 6px;";

/*********************************************************************
  constructor/destructor
*********************************************************************/

ModuleView::ModuleView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ModuleView)
{
    ui->setupUi(this);
	init();
}

ModuleView::ModuleView(const QString &title, const QString &description, QWidget *parent) :
  QWidget(parent),
  ui(new Ui::ModuleView)
{
    ui->setupUi(this);
	init();
	setModuleTitle(title);
    setModuleDescription(description);
}

ModuleView::~ModuleView()
{
    delete ui;
}

/*********************************************************************
  public methods
*********************************************************************/

void ModuleView::setModuleTitle(const QString &title)
{
    ui->lblTitle->setText(title);
}

void ModuleView::setModuleDescription(const QString &description)
{
    ui->lblDescription->setText(description);
}

void ModuleView::setStatusNormal(const QString &status)
{
    ui->lblStatus->setText(status);
	ui->lblStatus->setStyleSheet("color: darkblue; font-weight: bold");
    ui->lblTitle->setStyleSheet("color: black; font-weight: bold");
	ui->paneTitle->setStyleSheet(QString(contentPaneStyle) + "border-bottom: 1px solid silver; background-color: rgb(232, 232, 232); }");
	ui->paneContainer->setStyleSheet("#paneContainer { border: 1px solid silver; border-radius: 6px; background-color: white } ");
}

void ModuleView::setStatusPassed(const QString &status)
{
    ui->lblStatus->setText(status);
	ui->lblStatus->setStyleSheet("color: darkgreen; font-weight: bold");
	ui->lblTitle->setStyleSheet("color: black; font-weight: bold");
	ui->paneTitle->setStyleSheet(QString(contentPaneStyle) + "border-bottom: 1px solid black; background-color: rgb(213,223,208)}");
	ui->paneContainer->setStyleSheet("#paneContainer { border: 1px solid black; border-radius: 6px; background-color: rgb(230, 255, 230) }");
}

void ModuleView::setStatusFailed(const QString &status)
{
    ui->lblStatus->setText(status);
	ui->lblStatus->setStyleSheet("color: maroon; font-weight: bold");
	ui->lblTitle->setStyleSheet("color: black; font-weight: bold");
	ui->paneTitle->setStyleSheet(QString(contentPaneStyle) + "border-bottom: 1px solid black; background-color: rgb(223,213,208)}");
	ui->paneContainer->setStyleSheet("#paneContainer { border: 1px solid black; border-radius: 6px;"
        "background-color: rgb(255, 230, 230) }");
}

void ModuleView::setThreatScore(int score)
{
	if (score == 0)
		ui->lblThreatScore->setStyleSheet("color: darkgreen; font-weight: bold");
	else
		ui->lblThreatScore->setStyleSheet("color: maroon; font-weight: bold");

	ui->lblThreatScore->setText(QString("Threat Score: %1.").arg(score));

	if (ui->lblThreatScore->isHidden())
		ui->lblThreatScore->show();
}

void ModuleView::beforeRun()
{
	resetModule();
    setStatusNormal("Preparing to scan...");
}

void ModuleView::afterRun()
{
}

void ModuleView::addDetailWidget(QWidget *widget)
{
    ui->paneDetails->layout()->addWidget(widget);

    if (ui->btnToggleDetails->isHidden())
    {
		ui->btnToggleDetails->setText("Show Details");
		ui->btnToggleDetails->setIcon(expandIcon);
		ui->btnToggleDetails->show();
	}
 }

void ModuleView::addDetailLabel(const QString &text)
{
    QLabel *label = new QLabel(text);
    label->setWordWrap(true);
    addDetailWidget(label);
}

/*********************************************************************
  private/protected methods
*********************************************************************/

void ModuleView::init()
{
	// create a vboxlayout for the details pane
	QVBoxLayout *detailsLayout = new QVBoxLayout;
	detailsLayout->setAlignment(Qt::AlignTop);
	detailsLayout->setMargin(0);
	detailsLayout->setSpacing(4);
	ui->paneDetails->setLayout(detailsLayout);

	// check if we have created the details button icons
	if (expandIcon.isNull())
	{
		expandIcon = QIcon(QPixmap(":/Resources/Expand.png"));
		collapseIcon = QIcon(QPixmap(":/Resources/Collapse.png"));
	}

	resetModule();
	setStatusNormal("Scan not yet executed.");
}

void ModuleView::resetModule()
{
	// reset labels
	ui->lblStatus->setText(QString());
	ui->lblThreatScore->setText(QString());
	ui->lblThreatScore->hide();

	// clear the details pane
	QLayoutItem *child;

	while ((child = ui->paneDetails->layout()->takeAt(0)) != 0)
	{
		delete child->widget();
		delete child;
	}

	// reset the details pane and button
	ui->btnToggleDetails->setText("Show Details");
	ui->btnToggleDetails->setIcon(expandIcon);
	ui->btnToggleDetails->hide();
	ui->paneDetails->hide();
}

/*********************************************************************
  event handlers
*********************************************************************/

void ModuleView::on_btnToggleDetails_clicked()
{
    if (ui->paneDetails->isHidden())
    {
		ui->btnToggleDetails->setText("Hide Details");
		ui->btnToggleDetails->setIcon(collapseIcon);
		ui->paneDetails->show();
	}
    else
    {
		ui->btnToggleDetails->setText("Show Details");
		ui->btnToggleDetails->setIcon(expandIcon);
		ui->paneDetails->hide();
	}
}
