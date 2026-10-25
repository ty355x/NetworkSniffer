#-------------------------------------------------
#
# Project created by QtCreator 2012-01-24T16:48:58
#
#-------------------------------------------------

QT       += core gui

TARGET = NetworkSniffer
TEMPLATE = app

CONFIG   += precompile_header

SOURCES += main.cpp\
        mainwindow.cpp \
    mainview.cpp \
    moduleview.cpp \
    module.cpp \
    Modules/networkmodule.cpp \
    Modules/firewallmodule.cpp \
    Modules/windowsupdatemodule.cpp \
    Modules/wirelessadaptermodule.cpp \
    Modules/filesharingclientsmodule.cpp \
    Scans/firewall.cpp \
    Scans/network.cpp \
    Scans/p2p.cpp \
    Scans/wupdate.cpp \
    Scans/wireless.cpp \
    aboutdialog.cpp \
    modulemanager.cpp \
    summaryview.cpp \
    htmlwriter.cpp \
	License/licensewindow.cpp \
    License/licensestartview.cpp \
    License/webpageredirectview.cpp \
    License/enterlicenseview.cpp \
    License/licensemanager.cpp \
    License/sha1.cpp \
    License/registrationsuccessview.cpp

HEADERS  += mainwindow.h \
    mainview.h \
    moduleview.h \
    module.h \
    Modules/networkmodule.h \
    Modules/firewallmodule.h \
    Modules/windowsupdatemodule.h \
    Modules/filesharingclientsmodule.h \
    Modules/wirelessadaptermodule.h \
    Scans/firewall.h \
    Scans/network.h \
    Scans/p2p.h \
    Scans/wupdate.h \
    Scans/wireless.h \
    aboutdialog.h \
    modulemanager.h \
    summaryview.h \
    htmlwriter.h \
	License/licensewindow.h \
    License/licensestartview.h \
    License/webpageredirectview.h \
    License/enterlicenseview.h \
    License/licensemanager.h \
	precompiled.h \
    License/sha1.h \
    License/registrationsuccessview.h

PRECOMPILED_HEADER = precompiled.h

FORMS    += mainwindow.ui \
    mainview.ui \
    moduleview.ui \
    aboutdialog.ui \
    summaryview.ui \
    License/licensewindow.ui \
    License/licensestartview.ui \
    License/webpageredirectview.ui \
    License/enterlicenseview.ui \
    License/registrationsuccessview.ui

RESOURCES += \
    Resources.qrc

RC_FILE = NetworkSniffer.rc

#undefine unicode as the scan code isn't compatible with it
DEFINES -= UNICODE

# add the windows SDK header files
INCLUDEPATH += "C:\Dev\Microsoft\Microsoft SDKs\Windows\v6.1\Include"

# add the windows sdk lib files
LIBS += "C:\Dev\Microsoft\Microsoft SDKs\Windows\v6.1\Lib\advapi.lib"
LIBS += "C:\Dev\Microsoft\Microsoft SDKs\Windows\v6.1\Lib\mpr.lib"
LIBS += "C:\Dev\Microsoft\Microsoft SDKs\Windows\v6.1\Lib\ole32.lib"
LIBS += "C:\Dev\Microsoft\Microsoft SDKs\Windows\v6.1\Lib\oleaut32.lib"
LIBS += "C:\Dev\Microsoft\Microsoft SDKs\Windows\v6.1\Lib\wlanapi.lib"
LIBS += "C:\Dev\Microsoft\Microsoft SDKs\Windows\v6.1\Lib\wuguid.lib"
