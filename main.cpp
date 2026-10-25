/************************************************************************
  Program:		Network Sniffer
  File:			main.cpp
  Description:	Entry point for the network sniffer application.
  Author:		Taryk Tordjman
 ***********************************************************************/

#include "mainwindow.h"
#include "License/licensemanager.h";
#include "License/licensewindow.h";

#include <QDir>
#include <QFile>
#include <QTextStream>
#include <QtGui/QApplication>

QString loadStylesheet();

int main(int argc, char *argv[])
{
	// enable anti-aliased fonts
	QFont f = QApplication::font();
	f.setStyleStrategy((QFont::StyleStrategy)(QFont::PreferAntialias | QFont::PreferQuality));
	QApplication::setFont(f);

	// create the application object
	QApplication app(argc, argv);

	// set the application-wide stylesheet
	app.setStyleSheet(loadStylesheet());

	// add the plugins folder
	qApp->addLibraryPath(QDir::currentPath() + "/plugins");

	// initialize the license manager
	LicenseManager *license = LicenseManager::getInstance();
	license->readLicense();

	LicenseWindow wndLicense;

	if (license->isCurrentLicenseValid())
	{
		MainWindow::getInstance()->show();
	}
	else
	{
		wndLicense.show();
	}

	return app.exec();
}

QString loadStylesheet()
{
	// load AppStyles.css from the app resources
	QFile file(":/Resources/AppStyles.css");
	file.open(QIODevice::ReadOnly | QIODevice::Text);
	QTextStream in(&file);
	return in.readAll();
}
