#include "wireless.h"

bool GetWirelessNetworkInfo(LPSSFWACCESSPOINTLIST pAccessPoints)
{
	size_t temp_uint1 = 0;
	DWORD dwErr = 0;
	DWORD clientVersion = 1;
	HANDLE hClient = INVALID_HANDLE_VALUE;
	PWLAN_INTERFACE_INFO_LIST pInterfaceList = NULL;
	PWLAN_INTERFACE_INFO pInterface = NULL;
	PWLAN_PROFILE_INFO_LIST pProfileList = NULL;
	LPWSTR pProfileXML = NULL;

    if ((dwErr = WlanOpenHandle(clientVersion, NULL, &clientVersion, &hClient)) != ERROR_SUCCESS)
        return false;

    if ((dwErr = WlanEnumInterfaces(hClient, NULL, &pInterfaceList)) != ERROR_SUCCESS)
	{
		WlanCloseHandle(hClient, NULL);
        return false;
	}

	if (pInterfaceList->dwNumberOfItems == 0)
	{
        WlanFreeMemory(pInterfaceList);
		WlanCloseHandle(hClient, NULL);
        return false;
	}

	pInterface = &(pInterfaceList->InterfaceInfo[0]);

    for (DWORD i = 1; i < (pInterfaceList->dwNumberOfItems); i++)
	{
		switch (pInterfaceList->InterfaceInfo[i].isState)
		{
		case 1:	pInterface = &(pInterfaceList->InterfaceInfo[i]); break;
		case 2:	
			if ((pInterfaceList->InterfaceInfo[0].isState == 0)||(pInterfaceList->InterfaceInfo[0].isState == 4))
			{
				pInterface = &(pInterfaceList->InterfaceInfo[i]);
			}
			break;
		case 4:
			if (pInterfaceList->InterfaceInfo[0].isState == 0)
			{
				pInterface = &(pInterfaceList->InterfaceInfo[i]);
			}
			break;
		case 3:
		case 5:
		case 6:
		case 7:
			if ((pInterfaceList->InterfaceInfo[0].isState != 1)&&((pInterfaceList->InterfaceInfo[i].isState > (pInterfaceList->InterfaceInfo[0].isState))))
			{
				pInterface = &(pInterfaceList->InterfaceInfo[i]);
			}
			break;
		};
	}

	wcstombs_s(&temp_uint1, (pAccessPoints->adapter), 256, (pInterface->strInterfaceDescription), 255);

	if ((dwErr = WlanGetProfileList(hClient, &(pInterface->InterfaceGuid), NULL, &pProfileList)) != ERROR_SUCCESS)
	{
        WlanFreeMemory(pInterfaceList);
		WlanCloseHandle(hClient, NULL);
		return false;
	}

    for (DWORD i = 0; i < (pProfileList->dwNumberOfItems); i++)
	{
		if ((dwErr = WlanGetProfile(hClient, &(pInterface->InterfaceGuid), (pProfileList->ProfileInfo[i].strProfileName), NULL, &pProfileXML, NULL, NULL)) == ERROR_SUCCESS)
		{
			pAccessPoints->AddAccessPoint((pProfileList->ProfileInfo[i].strProfileName), pProfileXML);
			WlanFreeMemory(pProfileXML);
		}
	}

	WlanFreeMemory(pProfileList);
	WlanFreeMemory(pInterfaceList);
	WlanCloseHandle(hClient, NULL);
	return true;
}

SSFWACCESSPOINTLIST::SSFWACCESSPOINTLIST()
{
	ZeroMemory(this, sizeof(SSFWACCESSPOINTLIST));
}

SSFWACCESSPOINTLIST::~SSFWACCESSPOINTLIST()
{
    ClearAccessPoints();
}

void SSFWACCESSPOINTLIST::AddAccessPoint(const WCHAR *name, const WCHAR *profilexml)
{
	size_t temp_uint1 = 0;
	char *apname = NULL;
	char *approfile = NULL;
	char *auth = NULL;
	char *chptr = NULL;
	DWORD name_length = 0;
	DWORD profile_length = 0;
	DWORD auth_length = 0;
	char **temp_name = NULL;
	char **temp_authentication = NULL;

	if ((name == NULL)||(profilexml == NULL)) return;

	name_length = DWORD(wcslen(name));
	profile_length = DWORD(wcslen(profilexml));
	apname = new char [name_length + 2];
	ZeroMemory(apname, name_length + 2);
	approfile = new char [profile_length + 2];
	ZeroMemory(approfile, profile_length + 2);
	wcstombs_s(&temp_uint1, apname, name_length + 1, name, name_length);
	wcstombs_s(&temp_uint1, approfile, profile_length + 1, profilexml, profile_length);
	if (((chptr = strstr(approfile, "<authentication>")) == NULL)||(chptr[16] == 0)||(chptr[16] == '<')||(chptr[16] == '\r')||(chptr[16] == '\n'))
	{
		auth = new char [6];
		ZeroMemory(auth, 6);
		strncpy_s(auth, 5, "open\0\0", 4);
	}
	else
	{
		chptr += 16;
		auth_length = 0;
		while ((chptr[auth_length] != 0)&&(chptr[auth_length] != '<')&&(chptr[auth_length] != '\r')&&(chptr[auth_length] != '\n')) auth_length++;
		auth = new char [auth_length + 2];
		ZeroMemory(auth, auth_length + 2);
		strncpy_s(auth, auth_length + 1, chptr, auth_length);
	}

	temp_name = (this->name);
	temp_authentication = authentication;
	this->name = new char * [num_accesspoints + 1];
	authentication = new char * [num_accesspoints + 1];

    for (long i = 0; i < num_accesspoints; i++)
	{
		this->name[i] = (temp_name[i]);
		authentication[i] = (temp_authentication[i]);
	}

    this->name[num_accesspoints] = apname;
	authentication[num_accesspoints] = auth;
	num_accesspoints++;

	if (temp_name != NULL) delete [] temp_name;
	if (temp_authentication != NULL) delete [] temp_authentication;
	if (approfile != NULL) delete [] approfile;
}

void SSFWACCESSPOINTLIST::ClearAccessPoints()
{
    if ((name != NULL)&&(authentication != NULL))
    {
        for (long i = 0; i < num_accesspoints; i++)
        {
            if (name[i] != NULL) delete [] (name[i]);
            name[i] = NULL;

            if (authentication[i] != NULL) delete [] (authentication[i]);
            authentication[i] = NULL;
        }

        delete [] name;
        name = NULL;

        delete [] authentication;
        authentication = NULL;
    }

    ZeroMemory(this, sizeof(SSFWACCESSPOINTLIST));
}
