/************************************************************************************
  Program:		Network Sniffer
  File:			moduleview.h
  Description:	ModuleView class header file.
  Author:		Taryk Tordjman
 ***********************************************************************************/

#ifndef MODULEVIEW_H
#define MODULEVIEW_H

#include <QWidget>

namespace Ui {
class ModuleView;
}

/**
  A view widget that displays information about a module.
  Has a collapsible details pane that modules can use to add more detail widgets.
  The details pane is cleared every time the module is run and detail widgets need to be
  re-created by the module.
*/
class ModuleView : public QWidget
{
    Q_OBJECT
    
public:
    explicit ModuleView(QWidget *parent = 0);
    explicit ModuleView(const QString &title, const QString &description,
        QWidget *parent = NULL);
    ~ModuleView();

	/** Should be called before the module is run. */
	void beforeRun();

	/** Should be called after the module is run. */
	void afterRun();

	/** Sets the text displayed in the module title label. */
	void setModuleTitle(const QString &title);

	/** Sets the text displayed in the module description label. */
	void setModuleDescription(const QString &description);

	/** Sets the module status to normal and updates the status label. */
	void setStatusNormal(const QString &status);

	/** Sets the module status to passed and updates the status label. */
	void setStatusPassed(const QString &status);

	/** Sets the module status to failed and updates the status label. */
	void setStatusFailed(const QString &status);

	void setThreatScore(int score);

	/** Adds a widget to the details pane. */
	void addDetailWidget(QWidget *widget);

	/** Adds a label to the details pane.  This should be used to add a label instead of addDetailWidget
	  because it automatically sets desired label properties like wordwrap. */
	void addDetailLabel(const QString &text);

private slots:
    void on_btnToggleDetails_clicked();

private:
	void init();
	void resetModule();

	static QIcon expandIcon;
	static QIcon collapseIcon;
	const static char contentPaneStyle[];

	Ui::ModuleView *ui;
};

#endif // MODULEVIEW_H
