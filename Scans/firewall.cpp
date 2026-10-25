#include "firewall.h"

bool CheckFirewallEnabled()
{
	INetFwProfile* fwProfile = NULL;
	PWGSPH pWGSPH;
	WSC_SECURITY_PROVIDER_HEALTH sph;
	HMODULE wscapi = NULL;
	ZeroMemory(&sph, sizeof(WSC_SECURITY_PROVIDER_HEALTH));
   
	if ((pWGSPH = (PWGSPH) GetProcAddress((wscapi = LoadLibrary("wscapi.dll")), "WscGetSecurityProviderHealth")) != NULL)
	{
		if (pWGSPH(WSC_SECURITY_PROVIDER_FIREWALL, &sph) == S_OK)
		{
			if (sph == WSC_SECURITY_PROVIDER_HEALTH_GOOD) return true;
			return false;
		}
	}

	if (FAILED(GetWindowsFirewallProfile(&fwProfile))) return false;

	if (CheckWindowsFirewallIsOn(fwProfile))
	{
		fwProfile->Release();
		return true;
	}

	fwProfile->Release();
	FreeLibrary(wscapi);
	return false;
}

HRESULT GetWindowsFirewallProfile(INetFwProfile** fwProfile)
{
	INetFwMgr* fwMgr = NULL;
	INetFwPolicy* fwPolicy = NULL;
	if (fwProfile == NULL) return S_FALSE;
	*fwProfile = NULL;

	// Create an instance of the firewall settings manager.
    if (FAILED(CoCreateInstance(__uuidof(NetFwMgr), NULL, CLSCTX_INPROC_SERVER, __uuidof(INetFwMgr), (void**)&fwMgr)))
        return S_FALSE;

	// Retrieve the local firewall policy.
	if (FAILED(fwMgr->get_LocalPolicy(&fwPolicy)))
	{
		fwMgr->Release();
		return S_FALSE;
	}

	// Retrieve the firewall profile currently in effect.
	if (FAILED(fwPolicy->get_CurrentProfile(fwProfile)))
	{
		fwPolicy->Release();
		fwMgr->Release();
		return S_FALSE;
	}

	fwPolicy->Release();
	fwMgr->Release();
	return S_OK;
}

bool CheckWindowsFirewallIsOn(INetFwProfile* fwProfile)
{
	VARIANT_BOOL fwEnabled;
	if (fwProfile == NULL) return false;

	// Get the current state of the firewall.
	if (FAILED(fwProfile->get_FirewallEnabled(&fwEnabled))) return false;

	// Check to see if the firewall is on.
	if (fwEnabled != VARIANT_FALSE) return true;
	return false;
}
