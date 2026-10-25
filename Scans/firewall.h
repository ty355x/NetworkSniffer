#ifndef SSFW_FIREWALL
#define SSFW_FIREWALL

#include <windows.h>
#include <crtdbg.h>
#include <netfw.h>
#include <objbase.h>
#include <oleauto.h>
#include <stdio.h>

#ifndef _WSC_SECURITY_PROVIDER
typedef enum _WSC_SECURITY_PROVIDER
{
    // Represents the aggregation of all firewalls for this computer.
    WSC_SECURITY_PROVIDER_FIREWALL =                   0x1,
    // Represents the Automatic updating settings for this computer.
    WSC_SECURITY_PROVIDER_AUTOUPDATE_SETTINGS  =       0x2,
    // Represents the aggregation of all antivirus products for this comptuer.
    WSC_SECURITY_PROVIDER_ANTIVIRUS =                  0x4,
    // Represents the aggregation of all antispyware products for this comptuer.
    WSC_SECURITY_PROVIDER_ANTISPYWARE =                0x8,
    // Represents the settings that restrict the access of web sites in each of the internet zones.
    WSC_SECURITY_PROVIDER_INTERNET_SETTINGS =          0x10,
    // Represents the User Account Control settings on this machine.
    WSC_SECURITY_PROVIDER_USER_ACCOUNT_CONTROL =       0x20,
    // Represents the running state of the Security Center service on this machine.
    WSC_SECURITY_PROVIDER_SERVICE =                    0x40,

    WSC_SECURITY_PROVIDER_NONE =                       0,

    // Aggregates all of the items that Security Center monitors.
    WSC_SECURITY_PROVIDER_ALL =                             WSC_SECURITY_PROVIDER_FIREWALL | 
                                                            WSC_SECURITY_PROVIDER_AUTOUPDATE_SETTINGS | 
                                                            WSC_SECURITY_PROVIDER_ANTIVIRUS | 
                                                            WSC_SECURITY_PROVIDER_ANTISPYWARE | 
                                                            WSC_SECURITY_PROVIDER_INTERNET_SETTINGS | 
                                                            WSC_SECURITY_PROVIDER_USER_ACCOUNT_CONTROL | 
                                                            WSC_SECURITY_PROVIDER_SERVICE
} WSC_SECURITY_PROVIDER, *PWSC_SECURITY_PROVIDER;
#endif

#ifndef _WSC_SECURITY_PROVIDER_HEALTH
typedef enum _WSC_SECURITY_PROVIDER_HEALTH
{
    WSC_SECURITY_PROVIDER_HEALTH_GOOD, // Green pillar in English locales
    WSC_SECURITY_PROVIDER_HEALTH_NOTMONITORED, // Yellow pillar in English locales
    WSC_SECURITY_PROVIDER_HEALTH_POOR,  // Red pillar in English locales
    WSC_SECURITY_PROVIDER_HEALTH_SNOOZE, // Yellow pillar in English locales
} WSC_SECURITY_PROVIDER_HEALTH, *PWSC_SECURITY_PROVIDER_HEALTH;
#endif

typedef HRESULT (WINAPI *PWGSPH)(DWORD, PWSC_SECURITY_PROVIDER_HEALTH);

bool CheckFirewallEnabled();
HRESULT GetWindowsFirewallProfile(INetFwProfile** fwProfile);
bool CheckWindowsFirewallIsOn(INetFwProfile* fwProfile);

#endif
