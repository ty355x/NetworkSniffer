#include "network.h"

bool ListNetworkDevices(LPSSFWNETWORKDEVICE pNetworkDevices, LPNETRESOURCE pParentResource)
{
	HANDLE hEnum = INVALID_HANDLE_VALUE;
	DWORD dwErr = 0;
	DWORD num_resources = -1;
	DWORD resource_buffer_size = 1048576;
	LPNETRESOURCE pResources = NULL;
	LPSSFWNETWORKDEVICE pCurrentDevice = NULL;
	char type[17];
	char displayType[17];
	char name[261];
	char comment[261];
	bool container;

	if (pNetworkDevices == NULL)
		return false;

	if (pParentResource == NULL)
	{
		strncpy_s((pNetworkDevices->name), 260, "Entire Network\0\0", 15);
		pNetworkDevices->container = true;
	}

	if ((dwErr = WNetOpenEnum(RESOURCE_GLOBALNET, RESOURCETYPE_ANY, 0, pParentResource, &hEnum)) != NO_ERROR)
		return false;

	pResources = (LPNETRESOURCE) malloc(resource_buffer_size);
	ZeroMemory(pResources, resource_buffer_size);

	if ((dwErr = WNetEnumResource(hEnum, &num_resources, pResources, &resource_buffer_size)) != NO_ERROR)
	{
		free((void *) pResources);
		WNetCloseEnum(hEnum);
		return false;
	}

	for (DWORD i = 0; i < num_resources; i++)
	{
		ZeroMemory(type, 17);
		ZeroMemory(displayType, 17);
		ZeroMemory(name, 261);
		ZeroMemory(comment, 261);
		container = false;

		if (pResources[i].dwType & RESOURCETYPE_DISK)
			strncpy_s(type, 16, "Disk Resource\0\0", 14);
		else if (pResources[i].dwType & RESOURCETYPE_PRINT)
			strncpy_s(type, 16, "Print Resource\0\0", 15);

		switch (pResources[i].dwDisplayType)
		{
		case RESOURCEDISPLAYTYPE_GENERIC:
			strncpy_s(displayType, 16, "Generic\0\0", 8);
			break;
		case RESOURCEDISPLAYTYPE_DOMAIN:
			strncpy_s(displayType, 16, "Domain\0\0", 7);
			break;
		case RESOURCEDISPLAYTYPE_SERVER:
			strncpy_s(displayType, 16, "Server\0\0", 7);
			break;
		case RESOURCEDISPLAYTYPE_SHARE:
			strncpy_s(displayType, 16, "Shared\0\0", 7);
			break;
		case RESOURCEDISPLAYTYPE_FILE:
			strncpy_s(displayType, 16, "File\0\0", 5);
			break;
		case RESOURCEDISPLAYTYPE_GROUP:
			strncpy_s(displayType, 16, "Group\0\0", 6);
			break;
		case RESOURCEDISPLAYTYPE_NETWORK:
			strncpy_s(displayType, 16, "Network\0\0", 8);
			break;
		case RESOURCEDISPLAYTYPE_ROOT:
			strncpy_s(displayType, 16, "Entire Network\0\0", 15);
			break;
		case RESOURCEDISPLAYTYPE_SHAREADMIN:
			strncpy_s(displayType, 16, "Admin Share\0\0", 12);
			break;
		case RESOURCEDISPLAYTYPE_DIRECTORY:
			strncpy_s(displayType, 16, "Directory\0\0", 10);
			break;
		case RESOURCEDISPLAYTYPE_TREE:
			strncpy_s(displayType, 16, "NDS Tree\0\0", 9);
			break;
		case RESOURCEDISPLAYTYPE_NDSCONTAINER:
			strncpy_s(displayType, 16, "NDS Container\0\0", 14);
			break;
		default:
			strncpy_s(displayType, 16, "Unknown\0\0", 8);
		};

		if ((pResources[i].lpRemoteName != NULL)&&(pResources[i].lpRemoteName[0] != 0))
			strcpy_s(name, 260, (pResources[i].lpRemoteName));

		if ((pResources[i].lpComment != NULL)&&(pResources[i].lpComment[0] != 0))
			strcpy_s(comment, 260, (pResources[i].lpComment));

		if ((pResources[i].dwUsage & RESOURCEUSAGE_CONTAINER) == RESOURCEUSAGE_CONTAINER)
			container = true;

		pCurrentDevice = (pNetworkDevices->AddChild(type, displayType, name, comment, container));

		if (container)
			ListNetworkDevices(pCurrentDevice, &(pResources[i]));
	}

	free((void *) pResources);
	WNetCloseEnum(hEnum);
	return true;
}

SSFWNETWORKDEVICE::SSFWNETWORKDEVICE()
{
	ZeroMemory(this, sizeof(SSFWNETWORKDEVICE));
}

SSFWNETWORKDEVICE::~SSFWNETWORKDEVICE()
{
	if (pChildren != NULL)
	{
		for (long i = 0; i < num_children; i++)
		{
			if (pChildren[i] != NULL)
				delete (pChildren[i]);

			pChildren[i] = NULL;
		}
		delete [] pChildren;
	}

	pChildren = NULL;
}

LPSSFWNETWORKDEVICE SSFWNETWORKDEVICE::AddChild(const char *type, const char *displayType, const char *name, const char *comment, bool container)
{
	LPSSFWNETWORKDEVICE *pTempChildren = pChildren;
	pChildren = new LPSSFWNETWORKDEVICE [num_children + 1];

	for (long i = 0; i < num_children; i++)
		pChildren[i] = (pTempChildren[i]);

	pChildren[num_children] = new SSFWNETWORKDEVICE;
	strcpy_s((pChildren[num_children]->type), 16, type);
	strcpy_s((pChildren[num_children]->displayType), 16, displayType);
	strcpy_s((pChildren[num_children]->name), 260, name);
	strcpy_s((pChildren[num_children]->comment), 260, comment);
	pChildren[num_children]->container = container;

	if (pTempChildren != NULL)
		delete [] pTempChildren;

	return (pChildren[num_children++]);
}
