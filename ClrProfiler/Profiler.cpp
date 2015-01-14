// Profiler.cpp : Implementation of CProfiler

#include "stdafx.h"
#include "Profiler.h"

#include <iostream>

CProfiler* pICorProfilerCallback;

extern "C" void __stdcall EnterGlobalWithInfo(FunctionIDOrClientID functionIDOrClientID, COR_PRF_ELT_INFO eltInfo)
{
    if (pICorProfilerCallback != NULL)
        pICorProfilerCallback->Enter3WithInfo(functionIDOrClientID, eltInfo);
}

extern "C" void EnterNaked3WithInfo(FunctionIDOrClientID, COR_PRF_ELT_INFO);

//void __declspec(naked) EnterNaked3WithInfo(FunctionIDOrClientID functionIDOrClientID, COR_PRF_ELT_INFO eltInfo)
//{
//    __asm
//    {
//        push ebp
//            mov ebp, esp
//            pushad
//            mov edx, [ebp + 0x0C]
//            push edx
//            mov eax, [ebp + 0x08]
//            push eax
//            call EnterGlobalWithInfo;
//        popad
//            pop ebp
//            ret SIZE functionIDOrClientID + SIZE eltInfo
//    }
//}


extern "C" void __stdcall LeaveGlobalWithInfo(FunctionIDOrClientID functionIDOrClientID, COR_PRF_ELT_INFO eltInfo)
{
    if (pICorProfilerCallback != NULL)
        pICorProfilerCallback->Leave3WithInfo(functionIDOrClientID, eltInfo);
}

extern "C" void LeaveNaked3WithInfo(FunctionIDOrClientID functionIDOrClientID, COR_PRF_ELT_INFO eltInfo);
//{
//    __asm
//    {
//        push ebp
//            mov ebp, esp
//            pushad
//            mov edx, [ebp + 0x0C]
//            push edx
//            mov eax, [ebp + 0x08]
//            push eax
//            call LeaveGlobalWithInfo;
//        popad
//            pop ebp
//            ret SIZE functionIDOrClientID + SIZE eltInfo
//    }
//}
extern "C" void __stdcall TailcallGlobalWithInfo(FunctionIDOrClientID functionIDOrClientID, COR_PRF_ELT_INFO eltInfo)
{
    if (pICorProfilerCallback != NULL)
        pICorProfilerCallback->Tailcall3WithInfo(functionIDOrClientID, eltInfo);
}

extern "C" void TailcallNaked3WithInfo(FunctionIDOrClientID functionIDOrClientID, COR_PRF_ELT_INFO eltInfo);
//{
//    __asm
//    {
//        push ebp
//            mov ebp, esp
//            pushad
//            mov edx, [ebp + 0x0C]
//            push edx
//            mov eax, [ebp + 0x08]
//            push eax
//            call TailcallGlobalWithInfo;
//        popad
//            pop ebp
//            ret SIZE functionIDOrClientID + SIZE eltInfo
//    }
//}

void CProfiler::Enter3WithInfo(FunctionIDOrClientID functionIDOrClientID, COR_PRF_ELT_INFO eltInfo)
{
    FunctionID functionID = functionIDOrClientID.functionID;

    COR_PRF_FRAME_INFO frameInfo;
    ULONG cbArgumentInfo;
    //COR_PRF_FUNCTION_ARGUMENT_INFO argumentInfo;
    //HRESULT hr = pICorProfilerInfo4_->GetFunctionEnter3Info(functionID, eltInfo, &frameInfo, &cbArgumentInfo, &argumentInfo);


    std::cout << "Enter" << std::endl;
    
}

void CProfiler::Leave3WithInfo(FunctionIDOrClientID functionIDOrClientID, COR_PRF_ELT_INFO eltInfo)
{
    std::cout << "Leave" << std::endl;
}

void CProfiler::Tailcall3WithInfo(FunctionIDOrClientID functionIDOrClientID, COR_PRF_ELT_INFO eltInfo)
{
    std::cout << "Tailcall" << std::endl;
}

UINT_PTR __stdcall FunctionMapper(FunctionID functionID, void* clientData, BOOL* pbHookFunction)
{
    CProfiler* profiler = (CProfiler*)clientData;

    profiler->MapFunction(functionID);

    return functionID;
}

void CProfiler::MapFunction(FunctionID functionID)
{

}

HRESULT STDMETHODCALLTYPE CProfiler::Initialize(IUnknown *pICorProfilerInfoUnk)
{
    HRESULT result;

    std::cout << "started profiler" << std::endl;

    result = pICorProfilerInfoUnk->QueryInterface(IID_ICorProfilerInfo, (LPVOID*)&pICorProfilerInfo_);
    if (FAILED(result))
    {
        return E_FAIL;
    }

    result = pICorProfilerInfoUnk->QueryInterface(IID_ICorProfilerInfo2, (LPVOID*)&pICorProfilerInfo2_);
    if (FAILED(result))
    {
        return E_FAIL;
    }

    result = pICorProfilerInfoUnk->QueryInterface(IID_ICorProfilerInfo3, (LPVOID*)&pICorProfilerInfo3_);
    if (FAILED(result))
    {
        return E_FAIL;
    }

    result = pICorProfilerInfoUnk->QueryInterface(IID_ICorProfilerInfo4, (LPVOID*)&pICorProfilerInfo4_);
    if (FAILED(result))
    {
        return E_FAIL;
    }

    SetEventMasks();

    result = pICorProfilerInfo4_->SetEnterLeaveFunctionHooks3WithInfo((FunctionEnter3WithInfo*)EnterNaked3WithInfo, (FunctionLeave3WithInfo*)LeaveNaked3WithInfo, (FunctionTailcall3WithInfo*)TailcallNaked3WithInfo);
    if (FAILED(result))
    {
        return E_FAIL;
    }

    result = pICorProfilerInfo4_->SetFunctionIDMapper2(FunctionMapper, (void*)this);

    pICorProfilerCallback = this;
    return S_OK;
}


HRESULT STDMETHODCALLTYPE CProfiler::Shutdown(void)
{
    return S_OK;
}

void CProfiler::SetEventMasks()
{
    //COR_PRF_MONITOR_NONE = 0,
    //COR_PRF_MONITOR_FUNCTION_UNLOADS = 0x1,
    //COR_PRF_MONITOR_CLASS_LOADS = 0x2,
    //COR_PRF_MONITOR_MODULE_LOADS = 0x4,
    //COR_PRF_MONITOR_ASSEMBLY_LOADS = 0x8,
    //COR_PRF_MONITOR_APPDOMAIN_LOADS = 0x10,
    //COR_PRF_MONITOR_JIT_COMPILATION = 0x20,
    //COR_PRF_MONITOR_EXCEPTIONS = 0x40,
    //COR_PRF_MONITOR_GC = 0x80,
    //COR_PRF_MONITOR_OBJECT_ALLOCATED = 0x100,
    //COR_PRF_MONITOR_THREADS = 0x200,
    //COR_PRF_MONITOR_REMOTING = 0x400,
    //COR_PRF_MONITOR_CODE_TRANSITIONS = 0x800,
    //COR_PRF_MONITOR_ENTERLEAVE = 0x1000,
    //COR_PRF_MONITOR_CCW = 0x2000,
    //COR_PRF_MONITOR_REMOTING_COOKIE = (0x4000 | COR_PRF_MONITOR_REMOTING),
    //COR_PRF_MONITOR_REMOTING_ASYNC = (0x8000 | COR_PRF_MONITOR_REMOTING),
    //COR_PRF_MONITOR_SUSPENDS = 0x10000,
    //COR_PRF_MONITOR_CACHE_SEARCHES = 0x20000,
    //COR_PRF_ENABLE_REJIT = 0x40000,
    //COR_PRF_ENABLE_INPROC_DEBUGGING = 0x80000,
    //COR_PRF_ENABLE_JIT_MAPS = 0x100000,
    //COR_PRF_DISABLE_INLINING = 0x200000,
    //COR_PRF_DISABLE_OPTIMIZATIONS = 0x400000,
    //COR_PRF_ENABLE_OBJECT_ALLOCATED = 0x800000,
    //COR_PRF_MONITOR_CLR_EXCEPTIONS = 0x1000000,
    //COR_PRF_MONITOR_ALL = 0x107ffff,
    //COR_PRF_ENABLE_FUNCTION_ARGS = 0x2000000,
    //COR_PRF_ENABLE_FUNCTION_RETVAL = 0x4000000,
    //COR_PRF_ENABLE_FRAME_INFO = 0x8000000,
    //COR_PRF_ENABLE_STACK_SNAPSHOT = 0x10000000,
    //COR_PRF_USE_PROFILE_IMAGES = 0x20000000,
    //COR_PRF_DISABLE_TRANSPARENCY_CHECKS_UNDER_FULL_TRUST = 0x40000000,
    //COR_PRF_DISABLE_ALL_NGEN_IMAGES = 0x80000000,
    //COR_PRF_ALL = 0x8fffffff,
    //COR_PRF_REQUIRE_PROFILE_IMAGE = ((COR_PRF_USE_PROFILE_IMAGES | COR_PRF_MONITOR_CODE_TRANSITIONS) | COR_PRF_MONITOR_ENTERLEAVE),
    //COR_PRF_ALLOWABLE_AFTER_ATTACH = ((((((((COR_PRF_MONITOR_THREADS | COR_PRF_MONITOR_MODULE_LOADS) | COR_PRF_MONITOR_ASSEMBLY_LOADS) | COR_PRF_MONITOR_APPDOMAIN_LOADS) | COR_PRF_ENABLE_STACK_SNAPSHOT) | COR_PRF_MONITOR_GC) | COR_PRF_MONITOR_SUSPENDS) | COR_PRF_MONITOR_CLASS_LOADS) | COR_PRF_MONITOR_JIT_COMPILATION),
    //COR_PRF_MONITOR_IMMUTABLE = (((((((((((((((COR_PRF_MONITOR_CODE_TRANSITIONS | COR_PRF_MONITOR_REMOTING) | COR_PRF_MONITOR_REMOTING_COOKIE) | COR_PRF_MONITOR_REMOTING_ASYNC) | COR_PRF_ENABLE_REJIT) | COR_PRF_ENABLE_INPROC_DEBUGGING) | COR_PRF_ENABLE_JIT_MAPS) | COR_PRF_DISABLE_OPTIMIZATIONS) | COR_PRF_DISABLE_INLINING) | COR_PRF_ENABLE_OBJECT_ALLOCATED) | COR_PRF_ENABLE_FUNCTION_ARGS) | COR_PRF_ENABLE_FUNCTION_RETVAL) | COR_PRF_ENABLE_FRAME_INFO) | COR_PRF_USE_PROFILE_IMAGES) | COR_PRF_DISABLE_TRANSPARENCY_CHECKS_UNDER_FULL_TRUST) | COR_PRF_DISABLE_ALL_NGEN_IMAGES)

    pICorProfilerInfo4_->SetEventMask((DWORD)COR_PRF_MONITOR_ENTERLEAVE | COR_PRF_ENABLE_FUNCTION_ARGS | COR_PRF_ENABLE_FUNCTION_RETVAL | COR_PRF_ENABLE_FRAME_INFO);
}

// CProfiler

