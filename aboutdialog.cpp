/************************************************************************
  Program:		Network Sniffer
  File:			aboutdialog.cpp
  Description:	AboutDialog class implementation file.
  Author:		Taryk Tordjman
 ***********************************************************************/

#include "aboutdialog.h"
#include "ui_aboutdialog.h"

#include <QDesktopServices>
#include <QUrl>
#include <QProcess>

#define URL_NETSNIFFER_SITE ""

AboutDialog::AboutDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AboutDialog)
{
    ui->setupUi(this);

	// set the window flags to disable resizing and disable the help button
	Qt::WindowFlags flags = (windowFlags() | Qt::MSWindowsFixedSizeDialogHint) & ~Qt::WindowContextHelpButtonHint;
	setWindowFlags(flags);

	ui->headerLayout->setAlignment(Qt::AlignTop);

	ui->lblLink->setText(QString("<html>For terms of service, usage restrictions and other product information, please visit "
		"<a href='%1'>%1</a></html>").arg(URL_NETSNIFFER_SITE));
}

AboutDialog::~AboutDialog()
{
    delete ui;
}

void AboutDialog::on_btnClose_clicked()
{
    close();
}

void AboutDialog::on_lblLink_linkActivated(const QString &link)
{
	if (!link.startsWith("http://"))
		return;

	QDesktopServices::openUrl(link);
}
