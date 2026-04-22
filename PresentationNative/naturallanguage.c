#define COBJMACROS
#include <windows.h>

#include "wine/debug.h"

#include <initguid.h>
#include "naturallanguage.h"

WINE_DEFAULT_DEBUG_CHANNEL(nlg);

HRESULT NlLoad(void)
{
	return S_OK;
}

void NlUnload(void)
{
}

// ITextContext
typedef struct TextContext {
	ITextContext ITextContext_iface;
	LONG ref;
} TextContext;

static inline TextContext *impl_from_ITextContext(ITextContext *iface)
{
	return CONTAINING_RECORD(iface, TextContext, ITextContext_iface);
}

static HRESULT WINAPI TextContext_QueryInterface(ITextContext *iface, REFIID iid, void** ppv)
{
	TextContext *This = impl_from_ITextContext(iface);
	WINE_TRACE("(%p,%s,%p)\n", iface, debugstr_guid(iid), ppv);

	if (IsEqualIID(&IID_IUnknown, iid) ||
		IsEqualIID(&IID_ITextContext, iid))
	{
		*ppv = &This->ITextContext_iface;
	}
	else
	{
		*ppv = NULL;
		return E_NOINTERFACE;
	}
	IUnknown_AddRef((IUnknown*)*ppv);
	return S_OK;
}

static ULONG WINAPI TextContext_AddRef(ITextContext *iface)
{
	TextContext *This = impl_from_ITextContext(iface);
	ULONG ref = InterlockedIncrement(&This->ref);

	WINE_TRACE("(%p) refcount=%lu\n", iface, ref);

	return ref;
}

static ULONG WINAPI TextContext_Release(ITextContext *iface)
{
	TextContext *This = impl_from_ITextContext(iface);
	ULONG ref = InterlockedDecrement(&This->ref);

	WINE_TRACE("(%p) refcount=%lu\n", iface, ref);

	if (ref == 0)
		free(This);

	return ref;
}

static HRESULT WINAPI TextContext_ComStub(ITextContext *This)
{
	// Should never be called
	return E_NOTIMPL;
}

static HRESULT WINAPI TextContext_get_LexiconCount(ITextContext *iface, long *pval)
{
	WINE_FIXME("(%p,%p)\n", iface, pval);
	return E_NOTIMPL;
}

static HRESULT WINAPI TextContext_get_Lexicon(ITextContext *iface, long index, ILexicon **pval)
{
	WINE_FIXME("(%p,%li,%p)\n", iface, index, pval);
	return E_NOTIMPL;
}

static HRESULT WINAPI TextContext_AddLexicon(ITextContext *iface, ILexicon *pLexicon)
{
	WINE_FIXME("(%p,%p)\n", iface, pLexicon);
	return E_NOTIMPL;
}

static HRESULT WINAPI TextContext_RemoveLexicon(ITextContext *iface, ILexicon *pLexicon)
{
	WINE_FIXME("(%p,%p)\n", iface, pLexicon);
	return E_NOTIMPL;
}

static HRESULT WINAPI TextContext_get_Options(ITextContext *iface, IProcessingOptions **pval)
{
	WINE_FIXME("(%p,%p)\n", iface, pval);
	return E_NOTIMPL;
}

static HRESULT WINAPI TextContext_get_Capabilities(ITextContext *iface, LCID locale, IProcessingOptions **pval)
{
	WINE_FIXME("(%p,%lu,%p)\n", iface, locale, pval);
	return E_NOTIMPL;
}

static const ITextContextVtbl TextContext_Vtbl = {
	TextContext_QueryInterface,
	TextContext_AddRef,
	TextContext_Release,
	TextContext_ComStub,
	TextContext_ComStub,
	TextContext_ComStub,
	TextContext_ComStub,
	TextContext_ComStub,
	TextContext_ComStub,
	TextContext_ComStub,
	TextContext_get_LexiconCount,
	TextContext_get_Lexicon,
	TextContext_AddLexicon,
	TextContext_RemoveLexicon,
	TextContext_ComStub,
	TextContext_ComStub,
	TextContext_ComStub,
	TextContext_get_Options,
	TextContext_get_Capabilities,
	TextContext_ComStub,
	TextContext_ComStub,
	TextContext_ComStub,
	TextContext_ComStub,
	TextContext_ComStub,
	TextContext_ComStub,
	TextContext_ComStub,
	TextContext_ComStub,
	TextContext_ComStub,
	TextContext_ComStub,
	TextContext_ComStub,
	TextContext_ComStub,
	TextContext_ComStub,
	TextContext_ComStub,
	TextContext_ComStub,
	TextContext_ComStub,
	TextContext_ComStub,
	TextContext_ComStub,
	TextContext_ComStub,
	TextContext_ComStub,
	TextContext_ComStub,
	TextContext_ComStub,
	TextContext_ComStub,
	TextContext_ComStub,
	TextContext_ComStub,
	TextContext_ComStub,
	TextContext_ComStub,
	TextContext_ComStub,
	TextContext_ComStub,
	TextContext_ComStub,
	TextContext_ComStub,
	TextContext_ComStub,
	TextContext_ComStub,
	TextContext_ComStub,
	TextContext_ComStub,
	TextContext_ComStub,
	TextContext_ComStub,
	TextContext_ComStub,
	TextContext_ComStub,
	TextContext_ComStub,
	TextContext_ComStub,
	TextContext_ComStub,
	TextContext_ComStub,
	TextContext_ComStub
};

static HRESULT TextContext_Create(REFIID iid, void** ppv)
{
	TextContext *This;
	HRESULT res;

	This = malloc(sizeof(*This));
	if (!This) return E_OUTOFMEMORY;
	This->ITextContext_iface.lpVtbl = (ITextContextVtbl*)&TextContext_Vtbl;
	This->ref = 1;

	res = TextContext_QueryInterface(&This->ITextContext_iface, iid, ppv);
	TextContext_Release(&This->ITextContext_iface);

	return res;
}

// ITextChunk
typedef struct TextChunk {
	ITextChunk ITextChunk_iface;
	LONG ref;
	ITextContext *context;
	VARIANT_BOOL reuse_objects;
} TextChunk;

static inline TextChunk *impl_from_ITextChunk(ITextChunk *iface)
{
	return CONTAINING_RECORD(iface, TextChunk, ITextChunk_iface);
}

static HRESULT WINAPI TextChunk_QueryInterface(ITextChunk *iface, REFIID iid, void** ppv)
{
	TextChunk *This = impl_from_ITextChunk(iface);
	WINE_TRACE("(%p,%s,%p)\n", iface, debugstr_guid(iid), ppv);

	if (IsEqualIID(&IID_IUnknown, iid) ||
		IsEqualIID(&IID_ITextChunk, iid))
	{
		*ppv = &This->ITextChunk_iface;
	}
	else
	{
		*ppv = NULL;
		return E_NOINTERFACE;
	}
	IUnknown_AddRef((IUnknown*)*ppv);
	return S_OK;
}

static ULONG WINAPI TextChunk_AddRef(ITextChunk *iface)
{
	TextChunk *This = impl_from_ITextChunk(iface);
	ULONG ref = InterlockedIncrement(&This->ref);

	WINE_TRACE("(%p) refcount=%lu\n", iface, ref);

	return ref;
}

static ULONG WINAPI TextChunk_Release(ITextChunk *iface)
{
	TextChunk *This = impl_from_ITextChunk(iface);
	ULONG ref = InterlockedDecrement(&This->ref);

	WINE_TRACE("(%p) refcount=%lu\n", iface, ref);

	if (ref == 0)
	{
		if (This->context)
			ITextChunk_Release(This->context);
		free(This);
	}

	return ref;
}

static HRESULT WINAPI TextChunk_ComStub(ITextChunk *This)
{
	// Should never be called
	return E_NOTIMPL;
}

static HRESULT WINAPI TextChunk_SetInputArray(ITextChunk *iface, LPCWSTR str, LONG size)
{
	WINE_FIXME("(%p,%s,%li)\n", iface, debugstr_w(str), size);
	return E_NOTIMPL;
}

static HRESULT WINAPI TextChunk_get_Count(ITextChunk *iface, LONG *val)
{
	WINE_FIXME("(%p,%p)\n", iface, val);
	return E_NOTIMPL;
}

static HRESULT WINAPI TextChunk_get_Item(ITextChunk *iface, LONG index, ISentence **pval)
{
	WINE_FIXME("(%p,%ld,%p)\n", iface, index, pval);
	return E_NOTIMPL;
}

static HRESULT WINAPI TextChunk_get_Sentences(ITextChunk *iface, IEnumVARIANT **val)
{
	WINE_FIXME("(%p,%p)\n", iface, val);
	return E_NOTIMPL;
}

static HRESULT WINAPI TextChunk_get_Context(ITextChunk *iface, ITextContext **pval)
{
	TextChunk *This = impl_from_ITextChunk(iface);

	WINE_TRACE("(%p,%p)\n", iface, pval);

	if (This->context)
		ITextContext_AddRef(This->context);
	*pval = This->context;
	return S_OK;
}

static HRESULT WINAPI TextChunk_put_Context(ITextChunk *iface, ITextContext *val)
{
	TextChunk *This = impl_from_ITextChunk(iface);

	WINE_TRACE("(%p,%p)\n", iface, val);

	if (val)
		ITextContext_AddRef(val);
	if (This->context)
		ITextContext_Release(This->context);
	This->context = val;

	return S_OK;
}

static HRESULT WINAPI TextChunk_put_Locale(ITextChunk *iface, LCID val)
{
	WINE_FIXME("(%p,%lu)\n", iface, val);
	return E_NOTIMPL;
}

static HRESULT WINAPI TextChunk_GetEnumerator(ITextChunk *iface, IEnumVARIANT **ppSent)
{
	WINE_FIXME("(%p,%p)\n", iface, ppSent);
	return E_NOTIMPL;
}

static HRESULT WINAPI TextChunk_get_ReuseObjects(ITextChunk *iface, VARIANT_BOOL *pval)
{
	TextChunk *This = impl_from_ITextChunk(iface);
	WINE_TRACE("(%p,%p)\n", iface, pval);

	*pval = This->reuse_objects;

	return S_OK;
}

static HRESULT WINAPI TextChunk_put_ReuseObjects(ITextChunk *iface, VARIANT_BOOL val)
{
	TextChunk *This = impl_from_ITextChunk(iface);
	WINE_TRACE("(%p,%lu)\n", iface, val);

	This->reuse_objects = val ? VARIANT_TRUE : VARIANT_FALSE;

	return S_OK;
}

static const ITextChunkVtbl TextChunk_Vtbl = {
	TextChunk_QueryInterface,
	TextChunk_AddRef,
	TextChunk_Release,
	TextChunk_ComStub,
	TextChunk_ComStub,
	TextChunk_SetInputArray,
	TextChunk_ComStub,
	TextChunk_ComStub,
	TextChunk_ComStub,
	TextChunk_ComStub,
	TextChunk_ComStub,
	TextChunk_get_Count,
	TextChunk_get_Item,
	TextChunk_ComStub,
	TextChunk_get_Sentences,
	TextChunk_ComStub,
	TextChunk_ComStub,
	TextChunk_ComStub,
	TextChunk_get_Context,
	TextChunk_put_Context,
	TextChunk_ComStub,
	TextChunk_put_Locale,
	TextChunk_ComStub,
	TextChunk_ComStub,
	TextChunk_ComStub,
	TextChunk_ComStub,
	TextChunk_GetEnumerator,
	TextChunk_ComStub,
	TextChunk_ComStub,
	TextChunk_get_ReuseObjects,
	TextChunk_put_ReuseObjects
};

static HRESULT TextChunk_Create(REFIID iid, void** ppv)
{
	TextChunk *This;
	HRESULT res;

	This = malloc(sizeof(*This));
	if (!This) return E_OUTOFMEMORY;
	This->ITextChunk_iface.lpVtbl = (ITextChunkVtbl*)&TextChunk_Vtbl;
	This->ref = 1;
	This->context = NULL;
	This->reuse_objects = VARIANT_FALSE;

	res = TextChunk_QueryInterface(&This->ITextChunk_iface, iid, ppv);
	TextChunk_Release(&This->ITextChunk_iface);

	return res;
}

HRESULT NlGetClassObject(REFCLSID clsid, REFIID iid, void** ppv)
{
	if (IsEqualGUID(&CLSID_ITextChunk, clsid)) {
		return TextChunk_Create(iid, ppv);
	}
	if (IsEqualGUID(&CLSID_ITextContext, clsid)) {
		return TextContext_Create(iid, ppv);
	}
	WINE_FIXME("%s %s\n", wine_dbgstr_guid(clsid), wine_dbgstr_guid(iid));
	return E_NOTIMPL;
}

