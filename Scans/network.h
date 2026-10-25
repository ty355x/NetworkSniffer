#ifndef SSFW_NETWORK
#define SSFW_NETWORK

#include <windows.h>
#include <winnetwk.h>

typedef struct SSFWNETWORKDEVICE _SSFWNETWORKDEVICE;
typedef _SSFWNETWORKDEVICE *LPSSFWNETWORKDEVICE;

struct SSFWNETWORKDEVICE
{
	char type[17];
	char displayType[17];
	char name[261];
	char comment[261];

	bool container;
	long num_children;
	LPSSFWNETWORKDEVICE *pChildren;

	SSFWNETWORKDEVICE();
	~SSFWNETWORKDEVICE();

	LPSSFWNETWORKDEVICE AddChild(const char *type, const char *displayType, const char *name, const char *comment, bool container);
};

bool ListNetworkDevices(LPSSFWNETWORKDEVICE pNetworkDevices, LPNETRESOURCE pParentResource = NULL);

#endif
