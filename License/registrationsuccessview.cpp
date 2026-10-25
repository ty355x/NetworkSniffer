#include "registrationsuccessview.h"
#include "ui_registrationsuccessview.h"
#include "mainwindow.h"

RegistrationSuccessView::RegistrationSuccessView(LicenseWindow *window) :
	QWidget(NULL),
	window(window),
	ui(new Ui::RegistrationSuccessView)
{
	ui->setupUi(this);
}

RegistrationSuccessView::~RegistrationSuccessView()
{
	delete ui;
}

void RegistrationSuccessView::on_btnStart_clicked()
{
	window->close();
	MainWindow::getInstance()->show();
}
