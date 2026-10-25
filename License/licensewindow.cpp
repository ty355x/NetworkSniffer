#include "licensewindow.h"
#include "ui_licensewindow.h"
#include "../mainwindow.h"

#include <QGridLayout>

#define URL_REGISTER_APP ""
#define URL_RECOVER_REGISTRATION ""

/*************************************************
  constructor/destructor
 ************************************************/

LicenseWindow::LicenseWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::LicenseWindow)
{
	ui->setupUi(this);

	Qt::WindowFlags flags = (windowFlags() | Qt::MSWindowsFixedSizeDialogHint) & ~Qt::WindowContextHelpButtonHint;
	setWindowFlags(flags);

	// setup the main pane layout
	QGridLayout *mainLayout = new QGridLayout();
	mainLayout->setAlignment(Qt::AlignTop);
	mainLayout->setMargin(0);
	ui->paneMain->setLayout(mainLayout);

	createViews();
	showView(viewStart);
}

LicenseWindow::~LicenseWindow()
{
	delete ui;
}

/*************************************************
  public methods
************************************************/

void LicenseWindow::showStartView()
{
	showView(viewStart);
}

void LicenseWindow::showGetLicenseView()
{
	showView(viewGetLicense);
}

void LicenseWindow::showRecoverLicenseView()
{
	showView(viewRecoverLicense);
}

void LicenseWindow::showEnterLicenseView()
{
	showView(viewEnterLicense);
}

void LicenseWindow::showRegistrationSuccessView()
{
	showView(viewRegistrationSuccess);
}

void LicenseWindow::closeApp()
{
	close();
	QApplication::instance()->exit();
}

/*************************************************
	private methods
 ************************************************/

void LicenseWindow::createViews()
{
	viewStart = new LicenseStartView(this);

	viewGetLicense = new WebpageRedirectView(this,
		"Acquire License",
		"To acquire a network sniffer license, please visit the Network Sniffer website and fill out the registration form.",
		"Visit Registration Webpage",
		URL_REGISTER_APP);

	viewRecoverLicense = new WebpageRedirectView(this,
		"Recover License",
		"To recover your network sniffer license, please visit the Network Sniffer license recovery webpage and fill out the license recovery form.",
		"Visit Recovery Webpage",
		URL_RECOVER_REGISTRATION);

	viewEnterLicense = new EnterLicenseView(this);
	viewRegistrationSuccess = new RegistrationSuccessView(this);

	ui->paneMain->layout()->addWidget(viewStart);
	ui->paneMain->layout()->addWidget(viewGetLicense);
	ui->paneMain->layout()->addWidget(viewRecoverLicense);
	ui->paneMain->layout()->addWidget(viewEnterLicense);
	ui->paneMain->layout()->addWidget(viewRegistrationSuccess);
}

void LicenseWindow::hideAllViews()
{
	viewStart->hide();
	viewGetLicense->hide();
	viewRecoverLicense->hide();
	viewEnterLicense->hide();
	viewRegistrationSuccess->hide();
}

void LicenseWindow::showView(QWidget *view)
{
	hideAllViews();
	view->show();
}
