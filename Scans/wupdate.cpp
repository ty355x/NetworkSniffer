#include "wupdate.h"

void DateLastWindowsUpdate(LPSYSTEMTIME pSysTime)
{
	if (pSysTime == NULL) return;
	ZeroMemory(pSysTime, sizeof(SYSTEMTIME));

	IUpdateSearcher *pUpdateSearch;
	IUpdateHistoryEntryCollection *pCollection;
	IUpdateHistoryEntry *pEntry;
	long history_count = 0;
	DATE retval = 0;
	DATE current = 0;

	if (CoCreateInstance(CLSID_UpdateSearcher, NULL, CLSCTX_INPROC_SERVER | CLSCTX_LOCAL_SERVER ,IID_IUpdateSearcher, (VOID**)&pUpdateSearch) != S_OK) return;

	pUpdateSearch->GetTotalHistoryCount(&history_count);

	if (pUpdateSearch->QueryHistory(0, history_count, &pCollection) == S_OK)
	{
		for(long i = 0; i < history_count; i++)
		{
			if (pCollection->get_Item(i, &pEntry) == S_OK)
			{
				pEntry->get_Date(&current);
				if (current > retval) retval = current;
			}
		}
		pCollection->Release();
	}

	pUpdateSearch->Release();

	VariantTimeToSystemTime(retval, pSysTime);
}
