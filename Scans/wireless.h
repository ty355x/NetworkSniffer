#ifndef SSFW_WIRELESS
#define SSFW_WIRELESS

#include <windows.h>
#include <wlanapi.h>

typedef struct SSFWACCESSPOINTLIST _SSFWACCESSPOINTLIST;
typedef _SSFWACCESSPOINTLIST *LPSSFWACCESSPOINTLIST;

struct SSFWACCESSPOINTLIST
{
	char adapter[257];
	long num_accesspoints;
	char **name;
	char **authentication;

	SSFWACCESSPOINTLIST();
	~SSFWACCESSPOINTLIST();

	void AddAccessPoint(const WCHAR *name, const WCHAR *profilexml);
    void ClearAccessPoints();
};

bool GetWirelessNetworkInfo(LPSSFWACCESSPOINTLIST pAccessPoints);

#endif
