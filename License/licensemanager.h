#ifndef LICENSEMANAGER_H
#define LICENSEMANAGER_H

#include <QString>

/** Singleton class that manages persisting and validating license data. */
class LicenseManager
{
public:

	/** Return true if the current license data is valid. */
	bool isCurrentLicenseValid();

	/**
		Returns true if the specified license data is valid.  If the data is valid, it is
		saved.
	*/
	bool validateLicense(const QString &licenseName, const QString &licenseKey);

	/** Loads the saved license data. */
	void readLicense();

	/** Saves license data. */
	void saveLicense();

	/** Gets the instance of the license manager. */
	static LicenseManager *getInstance();

private:
	LicenseManager();
	LicenseManager(const LicenseManager &);
	LicenseManager &operator=(LicenseManager &);

	bool validateLicenseData(const QString &licenseName, const QString &licenseKey);
	void extractLicenseData(const QString &licenseName, const QString &licenseKey, uint &userId, QString &licenseNameOut);
	QString makeLicenseNameHash(uint userId, const QString &plaintext);

	static const char *publicKeyString;

	QString savedLicenseName;
	QString savedLicenseKey;
};

#endif // LICENSEMANAGER_H
