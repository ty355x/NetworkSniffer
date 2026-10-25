/************************************************************************
  Program:		Network Sniffer
  File:			summaryview.h
  Description:	SummaryView class header file.
  Author:		Taryk Tordjman
 ***********************************************************************/

#ifndef SUMMARYVIEW_H
#define SUMMARYVIEW_H

#include <QWidget>

namespace Ui {
	class SummaryView;
}


class SummaryView : public QWidget
{
	Q_OBJECT
	
public:
	explicit SummaryView(QWidget *parent = 0);
	~SummaryView();

	/** Sets the html to display in the module summary view. */
	void setHtml(const QString &html);

	/** Clears the html text. */
	void clearHtml();

private slots:
	void on_btnBack_clicked();

	void on_btnSave_clicked();

	void on_btnPrint_clicked();

private:
	Ui::SummaryView *ui;
};

#endif // SUMMARYVIEW_H
