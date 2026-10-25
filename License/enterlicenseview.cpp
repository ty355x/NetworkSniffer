#include "enterlicenseview.h"
#include "ui_enterlicenseview.h"
#include "licensemanager.h"
#include "../mainwindow.h"

#include <QMessageBox>

EnterLicenseView::EnterLicenseView(LicenseWindow *window) :
	QWidget(NULL),
	window(window),
	ui(new Ui::EnterLicenseView)
{
	ui->setupUi(this);
}

EnterLicenseView::~EnterLicenseView()
{
	delete ui;
}

void EnterLicenseView::on_btnConfirm_clicked()
{
	QString licName = ui->txtLicenseName->text().trimmed();
	QString licKey = ui->txtLicenseKey->text().trimmed();

	ui->txtLicenseName->setText(licName);
	ui->txtLicenseKey->setText(licKey);

	if (licName == NULL || licName.isEmpty())
	{
		QMessageBox::critical(this, "Unable to process license", "Please enter a license name");
		return;
	}

	if (licKey == NULL || licKey.isEmpty())
	{
		QMessageBox::critical(this, "Unable to process license", "Please enter a license key");
		return;
	}

	LicenseManager *license = LicenseManager::getInstance();

	if (license->validateLicense(licName, licKey))
	{	
		window->showRegistrationSuccessView();

	}
	else
	{
		QMessageBox::critical(this, "Unable to process license",
			"Sorry, Your license name and license key combination are not invalid.\n\n"
			"Please make sure that you are entering the correct license information.");
	}
}

void EnterLicenseView::on_btnBack_clicked()
{
	window->showStartView();
}

void EnterLicenseView::on_btnClose_clicked()
{
	window->closeApp();
}

