#ifndef LICENSEDETAILSPANE_H
#define LICENSEDETAILSPANE_H

#include <QWidget>

namespace Ui {
	class LicenseDetailsPane;
}

class LicenseDetailsPane : public QWidget
{
	Q_OBJECT
	
public:
	explicit LicenseDetailsPane(QWidget *parent = 0);
	~LicenseDetailsPane();
	
private:
	Ui::LicenseDetailsPane *ui;
};

#endif // LICENSEDETAILSPANE_H
