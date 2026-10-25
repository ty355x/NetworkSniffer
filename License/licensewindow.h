#ifndef LICENSEWINDOW_H
#define LICENSEWINDOW_H

#include "licensestartview.h"
#include "webpageredirectview.h"
#include "enterlicenseview.h"
#include "registrationsuccessview.h"
#include <QMainWindow>

namespace Ui {
	class LicenseWindow;
}

class LicenseStartView;
class WebpageRedirectView;
class EnterLicenseView;
class RegistrationSuccessView;

class LicenseWindow : public QMainWindow
{
	Q_OBJECT
	
public:
	explicit LicenseWindow(QWidget *parent = 0);
	~LicenseWindow();

	void showStartView();
	void showGetLicenseView();
	void showRecoverLicenseView();
	void showEnterLicenseView();
	void showRegistrationSuccessView();
	void closeApp();

private:
	void createViews();
	void hideAllViews();
	void showView(QWidget *view);

	LicenseStartView		*viewStart;
	WebpageRedirectView		*viewGetLicense;
	WebpageRedirectView		*viewRecoverLicense;
	EnterLicenseView		*viewEnterLicense;
	RegistrationSuccessView	*viewRegistrationSuccess;

	Ui::LicenseWindow *ui;
};

#endif // LICENSEWINDOW_H
