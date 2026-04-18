#include <windows.h>

#include "wine/debug.h"

WINE_DEFAULT_DEBUG_CHANNEL(nlg);

HRESULT NlLoad(void)
{
	return S_OK;
}

void NlUnload(void)
{
}

HRESULT NlGetClassObject(REFCLSID clsid, REFIID iid, void** ppv)
{
	WINE_FIXME("%s %s\n", wine_dbgstr_guid(clsid), wine_dbgstr_guid(iid));
	return E_NOTIMPL;
}

