#include "webpageredirectview.h"
#include "ui_webpageredirectview.h"

#include <QDesktopServices>
#include <QUrl>

WebpageRedirectView::WebpageRedirectView(LicenseWindow *window, const QString &title, const QString &details,
	const QString &buttonLabel, const QString &url) :
	QWidget(NULL),
	ui(new Ui::WebpageRedirectView)
{
	ui->setupUi(this);

	this->window = window;
	this->url = url;

	QString link = QString("<html>If your browser doesn't open when you click the button, open your "
	"browser manually and visit the webpage <a href='%1'>%1</a></html>").arg(url);

	ui->lblTitle->setText(title);
	ui->lblDetails->setText(details);
	ui->btnOpenPage->setText(buttonLabel);
	ui->lblLink->setText(link);
}

WebpageRedirectView::~WebpageRedirectView()
{
	delete ui;
}

void WebpageRedirectView::on_btnOpenPage_clicked()
{
	if (!url.startsWith("http://"))
		return;

	QDesktopServices::openUrl(QUrl(url));
}

void WebpageRedirectView::on_btnEnterLicense_clicked()
{
	window->showEnterLicenseView();
	window->close();
}

void WebpageRedirectView::on_btnBack_clicked()
{
	window->showStartView();
}

void WebpageRedirectView::on_btnClose_clicked()
{
	window->closeApp();
}
