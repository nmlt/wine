/*
 * UrlMon
 *
 * Copyright 1999 Corel Corporation
 *
 * Ulrich Czekalla
 *
 */

#include "windef.h"
#include "objbase.h"
#include "debugtools.h"

#include "urlmon.h"

DEFAULT_DEBUG_CHANNEL(urlmon);

/* native urlmon.dll uses this key, too */
static WCHAR BSCBHolder[] = { '_','B','S','C','B','_','H','o','l','d','e','r','_',0 };


/***********************************************************************
 *           CreateAsyncBindCtxEx (URLMON.@)
 *
 * not implemented
 *
 */
HRESULT WINAPI CreateAsyncBindCtxEx(IBindCtx *ibind, DWORD options,
    IBindStatusCallback *callback, IEnumFORMATETC *format, IBindCtx** pbind,
    DWORD reserved)
{
     FIXME("stub, returns failure\n");
     return E_INVALIDARG;
}


/***********************************************************************
 *           CreateURLMoniker (URLMON.@)
 *
 * Create a url moniker
 *
 * RETURNS
 *    S_OK 		success
 *    E_OUTOFMEMORY	out of memory 
 *    MK_E_SYNTAX	not a valid url
 *
 */
HRESULT WINAPI CreateURLMoniker(IMoniker *pmkContext, LPCWSTR szURL, IMoniker **ppmk)
{
   TRACE("\n");

   if (NULL != pmkContext)
	FIXME("Non-null pmkContext not implemented\n");

   return CreateFileMoniker(szURL, ppmk);
}

/***********************************************************************
 *           RegisterBindStatusCallback (URLMON.@)
 *
 * Register a bind status callback
 *
 * RETURNS
 *    S_OK 		success
 *    E_INVALIDARG  invalid argument(s)
 *    E_OUTOFMEMORY	out of memory 
 *
 */
HRESULT WINAPI RegisterBindStatusCallback(
    IBindCtx *pbc,
    IBindStatusCallback *pbsc,
    IBindStatusCallback **ppbscPrevious,
    DWORD dwReserved)
{
    IBindStatusCallback *prev;

	TRACE("(%p,%p,%p,%lu)\n", pbc, pbsc, ppbscPrevious, dwReserved);

    if (pbc == NULL || pbsc == NULL)
        return E_INVALIDARG;

    if (SUCCEEDED(IBindCtx_GetObjectParam(pbc, BSCBHolder, (IUnknown **)&prev)))
    {
        IBindCtx_RevokeObjectParam(pbc, BSCBHolder);
        if (ppbscPrevious)
            *ppbscPrevious = prev;
        else
            IBindStatusCallback_Release(prev);
    }
    
	return IBindCtx_RegisterObjectParam(pbc, BSCBHolder, (IUnknown *)pbsc);
}

/***********************************************************************
 *           RevokeBindStatusCallback (URLMON.@)
 *
 * Unregister a bind status callback
 *
 * RETURNS
 *    S_OK 		success
 *    E_INVALIDARG  invalid argument(s)
 *    E_FAIL pbsc wasn't registered with pbc
 *
 */
HRESULT WINAPI RevokeBindStatusCallback(
    IBindCtx *pbc,
    IBindStatusCallback *pbsc)
{
    IBindStatusCallback *callback;
    HRESULT hr = E_FAIL;

	TRACE("(%p,%p)\n", pbc, pbsc);

    if (pbc == NULL || pbsc == NULL)
        return E_INVALIDARG;

    if (SUCCEEDED(IBindCtx_GetObjectParam(pbc, BSCBHolder, (IUnknown **)&callback)))
    {
        if (callback == pbsc)
        {
            IBindCtx_RevokeObjectParam(pbc, BSCBHolder);
            hr = S_OK;
        }
        IBindStatusCallback_Release(pbsc);
    }

    return hr;
}

/***********************************************************************
 *           Extract (URLMON.@)
 *
 */
HRESULT WINAPI Extract(DWORD Param1, DWORD Param2)
{
   TRACE("%lx %lx\n", Param1, Param2);

   return S_OK;
}
