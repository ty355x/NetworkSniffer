#include "licensestartview.h"
#include "ui_licensestartview.h"

LicenseStartView::LicenseStartView(LicenseWindow *window) :
	QWidget(NULL),
	window(window),
	ui(new Ui::LicenseStartView)
{
	ui->setupUi(this);
	ui->btnNext->setEnabled(false);

	connect(ui->rdoEnterLicense, SIGNAL(clicked()), this, SLOT(onRadioButtonClick()));
	connect(ui->rdoGetLicense, SIGNAL(clicked()), this, SLOT(onRadioButtonClick()));
	connect(ui->rdoRecoverLicense, SIGNAL(clicked()), this, SLOT(onRadioButtonClick()));
}

LicenseStartView::~LicenseStartView()
{
	delete ui;
}

void LicenseStartView::onRadioButtonClick()
{
	ui->btnNext->setEnabled(true);
}

void LicenseStartView::on_btnNext_clicked()
{
	if (ui->rdoEnterLicense->isChecked())
		window->showEnterLicenseView();
	else if (ui->rdoGetLicense->isChecked())
		window->showGetLicenseView();
	else if (ui->rdoRecoverLicense->isChecked())
		window->showRecoverLicenseView();
}

void LicenseStartView::on_btnClose_clicked()
{
	window->closeApp();
}
