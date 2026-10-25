#ifndef ENTERLICENSEVIEW_H
#define ENTERLICENSEVIEW_H

#include "licensewindow.h"
#include <QWidget>

namespace Ui {
	class EnterLicenseView;
}

class LicenseWindow;

class EnterLicenseView : public QWidget
{
	Q_OBJECT
	
public:
	explicit EnterLicenseView(LicenseWindow *window);
	~EnterLicenseView();
	
private slots:
	void on_btnConfirm_clicked();
	void on_btnBack_clicked();
	void on_btnClose_clicked();

private:
	LicenseWindow *window;
	Ui::EnterLicenseView *ui;
};

#endif // ENTERLICENSEVIEW_H
