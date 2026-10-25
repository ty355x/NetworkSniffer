#include "licensemanager.h"
#include "Windows.h"
#include "sha1.h"

#include <exception>
#include <QByteArray>

/**************************************************************************************
	class constants
**************************************************************************************/

const char *LicenseManager::publicKeyString = "58hi3ro029asbo9";

/**************************************************************************************
	constructor
**************************************************************************************/

LicenseManager::LicenseManager() :
	savedLicenseName(QString()),
	savedLicenseKey(QString())
{
}

/**************************************************************************************
	static methods
**************************************************************************************/

LicenseManager *LicenseManager::getInstance()
{
	static LicenseManager instance = LicenseManager();
	return &instance;
}

/**************************************************************************************
	public methods
**************************************************************************************/

bool LicenseManager::isCurrentLicenseValid()
{
	return validateLicenseData(savedLicenseName, savedLicenseKey);
}

bool LicenseManager::validateLicense(const QString &licenseName, const QString &licenseKey)
{
	if (validateLicenseData(licenseName, licenseKey))
	{
		savedLicenseName = licenseName;
		savedLicenseKey = licenseKey;
		saveLicense();
		return true;
	}
	else
	{
		return false;
	}
}

void LicenseManager::readLicense()
{
	savedLicenseName = QString();
	savedLicenseKey = QString();

	char licenseName[256] = {0};
	char licenseKey[256] = {0};

	DWORD nameBufferSize = 256;
	DWORD keyBufferSize = 256;

	HKEY regKey;

	if (RegCreateKeyEx(HKEY_CURRENT_USER, "Software\\NetworkSniffer",
		0, NULL, REG_OPTION_VOLATILE, KEY_QUERY_VALUE, NULL, &regKey, NULL) != ERROR_SUCCESS)
	{
		throw new std::exception("Unable to open or create NetworkSniffer registry key.");
	}

	RegQueryValueEx(regKey, "License Name", NULL, NULL, (LPBYTE) licenseName, &nameBufferSize);
	RegQueryValueEx(regKey, "License Key", NULL, NULL, (LPBYTE) licenseKey, &keyBufferSize);
	RegCloseKey(regKey);

	if (strlen(licenseName) > 0 && strlen(licenseKey) > 0)
	{
		savedLicenseName = QString(licenseName);
		savedLicenseKey = QString(licenseKey);
	}
}

void LicenseManager::saveLicense()
{
	QByteArray licNameArray = savedLicenseName.toAscii();
	QByteArray licKeyArray = savedLicenseKey.toAscii();
	char *licName = licNameArray.data();
	char *licKey = licKeyArray.data();

	HKEY regKey;

	if (RegCreateKeyEx(HKEY_CURRENT_USER, "Software\\NetworkSniffer",
		0, NULL, REG_OPTION_VOLATILE, KEY_SET_VALUE, NULL, &regKey, NULL) != ERROR_SUCCESS)
	{
		throw new std::exception("Unable to open or create NetworkSniffer registry key.");
	}

	if (RegSetValueEx(regKey, "License Name", 0, REG_SZ, (BYTE*) licName, strlen(licName)) != ERROR_SUCCESS)
	{
		RegCloseKey(regKey);
		throw new std::exception("Unable to save NetworkSniffer registry data.");
	}

	if (RegSetValueEx(regKey, "License Key", 0, REG_SZ, (BYTE*) licKey, strlen(licKey)) != ERROR_SUCCESS)
	{
		RegCloseKey(regKey);
		throw new std::exception("Unable save NetworkSniffer registry data.");
	}

	RegCloseKey(regKey);
}

/**************************************************************************************
	private methods
**************************************************************************************/

bool LicenseManager::validateLicenseData(const QString &licenseName, const QString &licenseKey)
{
	// make sure we have license data to validate
	if (licenseName == NULL || licenseName.isEmpty() || licenseKey == NULL || licenseKey.isEmpty())
		return false;

	// extract the user id and the full license name
	uint userId;
	QString fullName = QString();
	extractLicenseData(licenseName, licenseKey, userId, fullName);

	if (userId == -1 || fullName == NULL || fullName.isEmpty())
		return false;

	// get the license name hash
	QString nameHash = makeLicenseNameHash(userId, fullName);

	if (nameHash == NULL || nameHash.isEmpty() || nameHash.length() != 32)
		return false;

	qDebug("Validating License Data:");
	qDebug(QString("License name: " + fullName).toAscii().data());
	qDebug(QString("License key: " + licenseKey).toAscii().data());
	qDebug(QString("Computed license key: " + nameHash.toUpper()).toAscii().data());

	// compare the name hash to the license key
	return nameHash.compare(licenseKey.toLower()) == 0;
}

void LicenseManager::extractLicenseData(const QString &licenseName, const QString &licenseKey,
	uint &userIdOut, QString &licenseNameOut)
{
	userIdOut = -1;
	licenseNameOut = QString();

	if (licenseName == NULL || licenseName.isEmpty() || licenseKey == NULL || licenseKey.isEmpty())
		return;

	// the license key must have 32 characters
	if (licenseKey.length() != 32)
		return;

	// extract the client id from the license string and convert it to decimal
	bool ok;
	QString userIdString = licenseKey.mid(6, 2) + licenseKey.mid(14, 2) + licenseKey.mid(22, 2) + licenseKey.mid(30, 2);
	userIdOut = userIdString.toUInt(&ok, 16);
	if (!ok) return;

	// conver the user id to a decimal string
	userIdString =  QString::number(userIdOut);

	// construct the license name
	licenseNameOut = userIdString + "_" + licenseName + "_" + publicKeyString;
	licenseNameOut = licenseNameOut.replace(' ', '_');
	licenseNameOut = licenseNameOut.toLower();
}

QString LicenseManager::makeLicenseNameHash(uint userId, const QString &licenseName)
{
	// convert the name from a qstring to a char array
	QByteArray nameBytes = licenseName.toAscii();
	char *nameChars = nameBytes.data();

	// hash the user name
	unsigned int hashResult[5];
	SHA1 sha;
	sha.Reset();
	sha << nameChars;
	sha.Result(hashResult);

	// convert the hash bytes to a hex qstring
	QString nameHash = QString();

	for (int i = 0; i < 5; i++)
		nameHash += QString("%1").arg((uint)hashResult[i], 8, 16, QChar('0'));

	// convert the id number to hex
	QString idHex = QString("%1").arg(userId, 8, 16, QChar('0'));

	// construct the hash
	QString hash = QString();
	hash += nameHash.mid(0, 6);
	hash += idHex.mid(0, 2);
	hash += nameHash.mid(6, 6);
	hash += idHex.mid(2, 2);
	hash += nameHash.mid(12, 6);
	hash += idHex.mid(4, 2);
	hash += nameHash.mid(18, 6);
	hash += idHex.mid(6, 2);
	hash = hash.toLower();

	return hash;
}
