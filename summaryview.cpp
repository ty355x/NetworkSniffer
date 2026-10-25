/************************************************************************
  Program:		Network Sniffer
  File:			summaryview.cpp
  Description:	SummaryView class implementation file.
  Author:		Taryk Tordjman
 ***********************************************************************/

#include "summaryview.h"
#include "ui_summaryview.h"
#include "mainwindow.h"

#include <QFileDialog>
#include <QMessageBox>
#include <QPrinter>
#include <QPrintDialog>
#include <QTextDocument>

SummaryView::SummaryView(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::SummaryView)
{
	ui->setupUi(this);
}

SummaryView::~SummaryView()
{
	delete ui;
}

void SummaryView::setHtml(const QString &html)
{
	ui->lblHtml->setText(html);
}

void SummaryView::clearHtml()
{
	ui->lblHtml->clear();
}

void SummaryView::on_btnBack_clicked()
{
	MainWindow::getInstance()->showMainView();
}

void SummaryView::on_btnSave_clicked()
{
	QString fileName = QFileDialog::getSaveFileName(this, "Save Log File", NULL, "Html Files (*.htm)");

	if (fileName == NULL || fileName.isEmpty())
		return;

	QFile file(fileName);

	if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
	{
		QMessageBox::critical(NULL, "Unable to save scan report",
			"Unable to open " + fileName + ".\n" + file.errorString());
		return;
	}

	file.write(ui->lblHtml->text().toUtf8().data());
}

void SummaryView::on_btnPrint_clicked()
{
	QPrinter printer;
	QPrintDialog *dialog = new QPrintDialog(&printer, this);
	dialog->setWindowTitle("Print Scan Report");

	if (dialog->exec() != QDialog::Accepted)
		return;

	QTextDocument doc;
	doc.setHtml(ui->lblHtml->text());
	doc.print(&printer);
}
