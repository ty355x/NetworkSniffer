#ifndef REGISTRATIONSUCCESSVIEW_H
#define REGISTRATIONSUCCESSVIEW_H

#include "licensewindow.h"
#include <QWidget>

namespace Ui {
	class RegistrationSuccessView;
}

class LicenseWindow;

class RegistrationSuccessView : public QWidget
{
	Q_OBJECT
	
public:
	explicit RegistrationSuccessView(LicenseWindow *window);
	~RegistrationSuccessView();
	
private slots:
	void on_btnStart_clicked();

private:
	LicenseWindow *window;
	Ui::RegistrationSuccessView *ui;
};

#endif // REGISTRATIONSUCCESSVIEW_H
