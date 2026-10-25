#ifndef WEBPAGEREDIRECTVIEW_H
#define WEBPAGEREDIRECTVIEW_H

#include "licensewindow.h"
#include <QWidget>

namespace Ui {
	class WebpageRedirectView;
}

class LicenseWindow;

class WebpageRedirectView : public QWidget
{
	Q_OBJECT
	
public:
	explicit WebpageRedirectView(LicenseWindow *window, const QString &title, const QString &details, const QString &buttonLabel,
		const QString &url);
	~WebpageRedirectView();
	
private slots:
	void on_btnOpenPage_clicked();
	void on_btnBack_clicked();
	void on_btnClose_clicked();
	void on_btnEnterLicense_clicked();

private:
	LicenseWindow *window;
	QString url;
	Ui::WebpageRedirectView *ui;
};

#endif // WEBPAGEREDIRECTVIEW_H
