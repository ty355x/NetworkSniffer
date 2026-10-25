/************************************************************************************
  Program:		Network Sniffer
  File:			aboutdialog.h
  Description:	AboutDialog class header file.
  Author:		Taryk Tordjman
 ***********************************************************************************/

#ifndef ABOUTDIALOG_H
#define ABOUTDIALOG_H

#include <QDialog>

namespace Ui {
class AboutDialog;
}

/** The about dialog box for the application. */
class AboutDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit AboutDialog(QWidget *parent = 0);
    ~AboutDialog();
    
private slots:
    void on_btnClose_clicked();

	void on_lblLink_linkActivated(const QString &link);

private:
    Ui::AboutDialog *ui;
};

#endif // ABOUTDIALOG_H
