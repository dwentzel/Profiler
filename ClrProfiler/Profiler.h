// Profiler.h : Declaration of the CProfiler

#pragma once
#include "resource.h"       // main symbols



#include "ClrProfiler_i.h"
#include "CorProfilerCallbackImpl.h"



#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Single-threaded COM objects are not properly supported on Windows CE platform, such as the Windows Mobile platforms that do not include full DCOM support. Define _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA to force ATL to support creating single-thread COM object's and allow use of it's single-threaded COM object implementations. The threading model in your rgs file was set to 'Free' as that is the only threading model supported in non DCOM Windows CE platforms."
#endif

using namespace ATL;


// CProfiler

class ATL_NO_VTABLE CProfiler :
    public CComObjectRootEx<CComSingleThreadModel>,
    public CComCoClass<CProfiler, &CLSID_Profiler>,
    public CCorProfilerCallbackImpl
{
public:
    CProfiler()
    {
    }

    DECLARE_REGISTRY_RESOURCEID(IDR_PROFILER)


    BEGIN_COM_MAP(CProfiler)
        COM_INTERFACE_ENTRY(ICorProfilerCallback)
        COM_INTERFACE_ENTRY(ICorProfilerCallback2)
        COM_INTERFACE_ENTRY(ICorProfilerCallback3)
        COM_INTERFACE_ENTRY(ICorProfilerCallback4)
        COM_INTERFACE_ENTRY(ICorProfilerCallback5)
    END_COM_MAP()

    DECLARE_PROTECT_FINAL_CONSTRUCT()

    HRESULT FinalConstruct()
    {
        return S_OK;
    }

    void FinalRelease()
    {
    }

    STDMETHOD(Initialize)(IUnknown *pICorProfilerInfoUnk);
    STDMETHOD(Shutdown)(void);

    void Enter3WithInfo(FunctionIDOrClientID functionIDOrClientID, COR_PRF_ELT_INFO eltInfo);
    void Leave3WithInfo(FunctionIDOrClientID functionIDOrClientID, COR_PRF_ELT_INFO eltInfo);
    void Tailcall3WithInfo(FunctionIDOrClientID functionIDOrClientID, COR_PRF_ELT_INFO eltInfo);

    void MapFunction(FunctionID functionID);

private:
    CComQIPtr<ICorProfilerInfo> pICorProfilerInfo_;
    CComQIPtr<ICorProfilerInfo2> pICorProfilerInfo2_;
    CComQIPtr<ICorProfilerInfo3> pICorProfilerInfo3_;
    CComQIPtr<ICorProfilerInfo4> pICorProfilerInfo4_;

    void SetEventMasks();



};

OBJECT_ENTRY_AUTO(__uuidof(Profiler), CProfiler)
