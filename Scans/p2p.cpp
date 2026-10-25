#include "p2p.h"

void ListProgramsP2P(LPSSFWP2PLIST pProgramsP2P)
{	
	DWORD temp_dword1 = 0;
	char buffer[16384] = {0};
	HKEY hUninstallKey = NULL;
	HKEY hUninstallKey64 = NULL;
	HKEY hKey = NULL;
	DWORD num_uninstall_keys = 0;
	char **uninstall_keys = NULL;
	DWORD num_uninstall_keys64 = 0;
	char **uninstall_keys64 = NULL;
	char **temp_keys = NULL;
	char programfiles[261] = {0};
	char programfilesx86[261] = {0};
	char programfilesx64[261] = {0};
	bool found = false;

	if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Uninstall", 0, KEY_READ | KEY_WOW64_32KEY, &hUninstallKey) == ERROR_SUCCESS)
	{
		num_uninstall_keys = 0;
		temp_dword1 = 16383;
		while (RegEnumKeyEx(hUninstallKey, num_uninstall_keys, buffer, &temp_dword1, NULL, NULL, NULL, NULL) == ERROR_SUCCESS)
		{
			temp_keys = uninstall_keys;
			uninstall_keys = new char * [num_uninstall_keys + 1];
			for (DWORD i = 0; i < num_uninstall_keys; i++) uninstall_keys[i] = (temp_keys[i]);
			uninstall_keys[num_uninstall_keys] = new char [temp_dword1 + 2];
			ZeroMemory((uninstall_keys[num_uninstall_keys]), temp_dword1 + 2);
			strncpy_s((uninstall_keys[num_uninstall_keys]), temp_dword1 + 1, buffer, temp_dword1);
			if (temp_keys != NULL) delete [] temp_keys;
			num_uninstall_keys++;
			temp_dword1 = 16383;
		}
	}

	if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Uninstall", 0, KEY_READ | KEY_WOW64_64KEY, &hUninstallKey64) == ERROR_SUCCESS)
	{
		num_uninstall_keys64 = 0;
		temp_dword1 = 16383;
		while (RegEnumKeyEx(hUninstallKey64, num_uninstall_keys64, buffer, &temp_dword1, NULL, NULL, NULL, NULL) == ERROR_SUCCESS)
		{
			temp_keys = uninstall_keys64;
			uninstall_keys64 = new char * [num_uninstall_keys64 + 1];
			for (DWORD i = 0; i < num_uninstall_keys64; i++) uninstall_keys64[i] = (temp_keys[i]);
			uninstall_keys64[num_uninstall_keys64] = new char [temp_dword1 + 2];
			ZeroMemory((uninstall_keys64[num_uninstall_keys64]), temp_dword1 + 2);
			strncpy_s((uninstall_keys64[num_uninstall_keys64]), temp_dword1 + 1, buffer, temp_dword1);
			if (temp_keys != NULL) delete [] temp_keys;
			num_uninstall_keys64++;
			temp_dword1 = 16383;
		}
	}

	ExpandEnvironmentStrings("%ProgramFiles%", programfiles, 260);
	ExpandEnvironmentStrings("%ProgramFiles(X86)%", programfilesx86, 260);
	ExpandEnvironmentStrings("%ProgramW6432%", programfilesx64, 260);
	if (programfiles[0] != 0) strncat_s(programfiles, 260, "\\", 1);
	if (programfilesx86[0] != 0) strncat_s(programfilesx86, 260, "\\", 1);
	if (programfilesx64[0] != 0) strncat_s(programfilesx64, 260, "\\", 1);

	for (long i = 0; i < P2P_COUNT; i++)
	{
		found = false;
		for (DWORD k = 0; k < num_uninstall_keys; k++)
		{
			if (strncmp((uninstall_keys[k]), (P2P_KEYS[i]), strlen(P2P_KEYS[i])) == 0)
			{
				found = true;
				k = num_uninstall_keys;
			}
			else
			{
				temp_dword1 = 16383;
				if (RegOpenKey(hUninstallKey, (uninstall_keys[k]), &hKey) == ERROR_SUCCESS)
				{
					ZeroMemory(buffer, 16384);
					if (RegQueryValueEx(hKey, "DisplayName", NULL, NULL, (unsigned char *) buffer, &temp_dword1) == ERROR_SUCCESS)
					{
						if (strncmp((uninstall_keys[k]), (P2P_DISPLAYNAMES[i]), strlen(P2P_DISPLAYNAMES[i])) == 0)
						{
							found = true;
							k = num_uninstall_keys;
						}
					}
					RegCloseKey(hKey);
				}
			}
		}
		if (found == false)
		{
			for (DWORD k = 0; k < num_uninstall_keys64; k++)
			{
				if (strncmp((uninstall_keys64[k]), (P2P_KEYS[i]), strlen(P2P_KEYS[i])) == 0)
				{
					found = true;
					k = num_uninstall_keys64;
				}
				else
				{
					temp_dword1 = 16383;
					if (RegOpenKey(hUninstallKey64, (uninstall_keys64[k]), &hKey) == ERROR_SUCCESS)
					{
						ZeroMemory(buffer, 16384);
						if (RegQueryValueEx(hKey, "DisplayName", NULL, NULL, (unsigned char *) buffer, &temp_dword1) == ERROR_SUCCESS)
						{
							if (strncmp((uninstall_keys64[k]), (P2P_DISPLAYNAMES[i]), strlen(P2P_DISPLAYNAMES[i])) == 0)
							{
								found = true;
								k = num_uninstall_keys64;
							}
							RegCloseKey(hKey);
						}
					}
				}
			}
		}
		if ((found == false)&&(programfiles[0] != 0))
		{
			ZeroMemory(buffer, 16384);
			strcpy_s(buffer, 16383, programfiles);
			strcat_s(buffer, 16383, P2P_PATHS[i]);
			if (FileExists(buffer)) found = true;
		}
		if ((found == false)&&(programfilesx86[0] != 0))
		{
			ZeroMemory(buffer, 16384);
			strcpy_s(buffer, 16383, programfilesx86);
			strcat_s(buffer, 16383, P2P_PATHS[i]);
			if (FileExists(buffer)) found = true;
		}
		if ((found == false)&&(programfilesx64[0] != 0))
		{
			ZeroMemory(buffer, 16384);
			strcpy_s(buffer, 16383, programfilesx64);
			strcat_s(buffer, 16383, P2P_PATHS[i]);
			if (FileExists(buffer)) found = true;
		}
		if (found) pProgramsP2P->AddProgram(P2P_NAMES[i]);
	}

	if (uninstall_keys != NULL)
	{
		for (DWORD i = 0; i < num_uninstall_keys; i++)
		{
			if (uninstall_keys[i] != NULL) delete [] (uninstall_keys[i]);
			uninstall_keys[i] = NULL;
		}
		delete [] uninstall_keys;
	}
	if (uninstall_keys64 != NULL)
	{
		for (DWORD i = 0; i < num_uninstall_keys64; i++)
		{
			if (uninstall_keys64[i] != NULL) delete [] (uninstall_keys64[i]);
			uninstall_keys64[i] = NULL;
		}
		delete [] uninstall_keys64;
	}

	if (hUninstallKey != NULL) RegCloseKey(hUninstallKey);
	if (hUninstallKey64 != NULL) RegCloseKey(hUninstallKey64);
}

SSFWP2PLIST::SSFWP2PLIST()
{
	ZeroMemory(this, sizeof(SSFWP2PLIST));
}

SSFWP2PLIST::~SSFWP2PLIST()
{
	if (name != NULL)
	{
		for (long i = 0; i < num_p2ps; i++)
		{
			if (name[i] != NULL) delete [] (name[i]);
			name[i] = NULL;
		}
		delete [] name;
	}
	name = NULL;
}

void SSFWP2PLIST::AddProgram(const char *name)
{
	DWORD name_length = 0;
	char **temp_name = (this->name);
	if ((name == NULL)||(name[0] == 0)) return;
	name_length = DWORD(strlen(name));
	this->name = new char * [num_p2ps + 1];
	for (long i = 0; i < num_p2ps; i++) this->name[i] = (temp_name[i]);
	this->name[num_p2ps] = new char [name_length + 2];
	ZeroMemory((this->name[num_p2ps]), name_length + 2);
	strncpy_s((this->name[num_p2ps]), name_length + 1, name, name_length);
	if (temp_name != NULL) delete [] temp_name;
	num_p2ps++;
}

bool FileExists(const char *filename)
{
	DWORD temp_dword1 = 0;
	temp_dword1 = GetFileAttributes(filename);
	
	if ((temp_dword1 != INVALID_FILE_ATTRIBUTES)&&((temp_dword1 & FILE_ATTRIBUTE_DIRECTORY) == 0)) return true;
	return false;
}
