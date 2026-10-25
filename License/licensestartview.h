#ifndef LICENSESTARTVIEW_H
#define LICENSESTARTVIEW_H

#include "licensewindow.h"
#include <QWidget>

namespace Ui {
	class LicenseStartView;
}

class LicenseWindow;

class LicenseStartView : public QWidget
{
	Q_OBJECT
	
public:
	explicit LicenseStartView(LicenseWindow *window);
	~LicenseStartView();

private:
	LicenseWindow *window;
	Ui::LicenseStartView *ui;

private slots:
	void onRadioButtonClick();
	void on_btnNext_clicked();
	void on_btnClose_clicked();
};

#endif // LICENSESTARTVIEW_H
