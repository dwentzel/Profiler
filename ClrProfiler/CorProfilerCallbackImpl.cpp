#include "stdafx.h"
#include "CorProfilerCallbackImpl.h"


CCorProfilerCallbackImpl::CCorProfilerCallbackImpl()
{
}


CCorProfilerCallbackImpl::~CCorProfilerCallbackImpl()
{
}

HRESULT STDMETHODCALLTYPE CCorProfilerCallbackImpl::Initialize(IUnknown *pICorProfilerInfoUnk)
{
    return S_OK;
}


HRESULT STDMETHODCALLTYPE CCorProfilerCallbackImpl::Shutdown(void)
{
    return S_OK;
}


HRESULT STDMETHODCALLTYPE CCorProfilerCallbackImpl::AppDomainCreationStarted(AppDomainID appDomainId)
{
    return S_OK;
}


HRESULT STDMETHODCALLTYPE CCorProfilerCallbackImpl::AppDomainCreationFinished(AppDomainID appDomainId, HRESULT hrStatus)
{
    return S_OK;
}


HRESULT STDMETHODCALLTYPE CCorProfilerCallbackImpl::AppDomainShutdownStarted(AppDomainID appDomainId)
{
    return S_OK;
}


HRESULT STDMETHODCALLTYPE CCorProfilerCallbackImpl::AppDomainShutdownFinished(AppDomainID appDomainId, HRESULT hrStatus)
{
    return S_OK;
}


HRESULT STDMETHODCALLTYPE CCorProfilerCallbackImpl::AssemblyLoadStarted(AssemblyID assemblyId)
{
    return S_OK;
}


HRESULT STDMETHODCALLTYPE CCorProfilerCallbackImpl::AssemblyLoadFinished(AssemblyID assemblyId, HRESULT hrStatus)
{
    return S_OK;
}


HRESULT STDMETHODCALLTYPE CCorProfilerCallbackImpl::AssemblyUnloadStarted(AssemblyID assemblyId)
{
    return S_OK;
}


HRESULT STDMETHODCALLTYPE CCorProfilerCallbackImpl::AssemblyUnloadFinished(AssemblyID assemblyId, HRESULT hrStatus)
{
    return S_OK;
}


HRESULT STDMETHODCALLTYPE CCorProfilerCallbackImpl::ModuleLoadStarted(ModuleID moduleId)
{
    return S_OK;
}


HRESULT STDMETHODCALLTYPE CCorProfilerCallbackImpl::ModuleLoadFinished(ModuleID moduleId, HRESULT hrStatus)
{
    return S_OK;
}


HRESULT STDMETHODCALLTYPE CCorProfilerCallbackImpl::ModuleUnloadStarted(ModuleID moduleId)
{
    return S_OK;
}


HRESULT STDMETHODCALLTYPE CCorProfilerCallbackImpl::ModuleUnloadFinished(ModuleID moduleId, HRESULT hrStatus)
{
    return S_OK;
}


HRESULT STDMETHODCALLTYPE CCorProfilerCallbackImpl::ModuleAttachedToAssembly(ModuleID moduleId, AssemblyID AssemblyId)
{
    return S_OK;
}


HRESULT STDMETHODCALLTYPE CCorProfilerCallbackImpl::ClassLoadStarted(ClassID classId)
{
    return S_OK;
}


HRESULT STDMETHODCALLTYPE CCorProfilerCallbackImpl::ClassLoadFinished(ClassID classId, HRESULT hrStatus)
{
    return S_OK;
}


HRESULT STDMETHODCALLTYPE CCorProfilerCallbackImpl::ClassUnloadStarted(ClassID classId)
{
    return S_OK;
}


HRESULT STDMETHODCALLTYPE CCorProfilerCallbackImpl::ClassUnloadFinished(ClassID classId, HRESULT hrStatus)
{
    return S_OK;
}


HRESULT STDMETHODCALLTYPE CCorProfilerCallbackImpl::FunctionUnloadStarted(FunctionID functionId)
{
    return S_OK;
}


HRESULT STDMETHODCALLTYPE CCorProfilerCallbackImpl::JITCompilationStarted(FunctionID functionId, BOOL fIsSafeToBlock)
{
    return S_OK;
}


HRESULT STDMETHODCALLTYPE CCorProfilerCallbackImpl::JITCompilationFinished(FunctionID functionId, HRESULT hrStatus, BOOL fIsSafeToBlock)
{
    return S_OK;
}


HRESULT STDMETHODCALLTYPE CCorProfilerCallbackImpl::JITCachedFunctionSearchStarted(FunctionID functionId, BOOL *pbUseCachedFunction)
{
    return S_OK;
}


HRESULT STDMETHODCALLTYPE CCorProfilerCallbackImpl::JITCachedFunctionSearchFinished(FunctionID functionId, COR_PRF_JIT_CACHE result)
{
    return S_OK;
}


HRESULT STDMETHODCALLTYPE CCorProfilerCallbackImpl::JITFunctionPitched(FunctionID functionId)
{
    return S_OK;
}


HRESULT STDMETHODCALLTYPE CCorProfilerCallbackImpl::JITInlining(FunctionID callerId, FunctionID calleeId, BOOL *pfShouldInline)
{
    return S_OK;
}


HRESULT STDMETHODCALLTYPE CCorProfilerCallbackImpl::ThreadCreated(ThreadID threadId)
{
    return S_OK;
}


HRESULT STDMETHODCALLTYPE CCorProfilerCallbackImpl::ThreadDestroyed(ThreadID threadId)
{
    return S_OK;
}


HRESULT STDMETHODCALLTYPE CCorProfilerCallbackImpl::ThreadAssignedToOSThread(ThreadID managedThreadId, DWORD osThreadId)
{
    return S_OK;
}


HRESULT STDMETHODCALLTYPE CCorProfilerCallbackImpl::RemotingClientInvocationStarted(void)
{
    return S_OK;
}


HRESULT STDMETHODCALLTYPE CCorProfilerCallbackImpl::RemotingClientSendingMessage(GUID *pCookie, BOOL fIsAsync)
{
    return S_OK;
}


HRESULT STDMETHODCALLTYPE CCorProfilerCallbackImpl::RemotingClientReceivingReply(GUID *pCookie, BOOL fIsAsync)
{
    return S_OK;
}


HRESULT STDMETHODCALLTYPE CCorProfilerCallbackImpl::RemotingClientInvocationFinished(void)
{
    return S_OK;
}


HRESULT STDMETHODCALLTYPE CCorProfilerCallbackImpl::RemotingServerReceivingMessage(GUID *pCookie, BOOL fIsAsync)
{
    return S_OK;
}


HRESULT STDMETHODCALLTYPE CCorProfilerCallbackImpl::RemotingServerInvocationStarted(void)
{
    return S_OK;
}


HRESULT STDMETHODCALLTYPE CCorProfilerCallbackImpl::RemotingServerInvocationReturned(void)
{
    return S_OK;
}


HRESULT STDMETHODCALLTYPE CCorProfilerCallbackImpl::RemotingServerSendingReply(GUID *pCookie, BOOL fIsAsync)
{
    return S_OK;
}


HRESULT STDMETHODCALLTYPE CCorProfilerCallbackImpl::UnmanagedToManagedTransition(FunctionID functionId, COR_PRF_TRANSITION_REASON reason)
{
    return S_OK;
}


HRESULT STDMETHODCALLTYPE CCorProfilerCallbackImpl::ManagedToUnmanagedTransition(FunctionID functionId, COR_PRF_TRANSITION_REASON reason)
{
    return S_OK;
}


HRESULT STDMETHODCALLTYPE CCorProfilerCallbackImpl::RuntimeSuspendStarted(COR_PRF_SUSPEND_REASON suspendReason)
{
    return S_OK;
}


HRESULT STDMETHODCALLTYPE CCorProfilerCallbackImpl::RuntimeSuspendFinished(void)
{
    return S_OK;
}


HRESULT STDMETHODCALLTYPE CCorProfilerCallbackImpl::RuntimeSuspendAborted(void)
{
    return S_OK;
}


HRESULT STDMETHODCALLTYPE CCorProfilerCallbackImpl::RuntimeResumeStarted(void)
{
    return S_OK;
}


HRESULT STDMETHODCALLTYPE CCorProfilerCallbackImpl::RuntimeResumeFinished(void)
{
    return S_OK;
}


HRESULT STDMETHODCALLTYPE CCorProfilerCallbackImpl::RuntimeThreadSuspended(ThreadID threadId)
{
    return S_OK;
}


HRESULT STDMETHODCALLTYPE CCorProfilerCallbackImpl::RuntimeThreadResumed(ThreadID threadId)
{
    return S_OK;
}


HRESULT STDMETHODCALLTYPE CCorProfilerCallbackImpl::MovedReferences(ULONG cMovedObjectIDRanges, ObjectID oldObjectIDRangeStart[], ObjectID newObjectIDRangeStart[], ULONG cObjectIDRangeLength[])
{
    return S_OK;
}


HRESULT STDMETHODCALLTYPE CCorProfilerCallbackImpl::ObjectAllocated(ObjectID objectId, ClassID classId)
{
    return S_OK;
}


HRESULT STDMETHODCALLTYPE CCorProfilerCallbackImpl::ObjectsAllocatedByClass(ULONG cClassCount, ClassID classIds[], ULONG cObjects[])
{
    return S_OK;
}


HRESULT STDMETHODCALLTYPE CCorProfilerCallbackImpl::ObjectReferences(ObjectID objectId, ClassID classId, ULONG cObjectRefs, ObjectID objectRefIds[])
{
    return S_OK;
}


HRESULT STDMETHODCALLTYPE CCorProfilerCallbackImpl::RootReferences(ULONG cRootRefs, ObjectID rootRefIds[])
{
    return S_OK;
}


HRESULT STDMETHODCALLTYPE CCorProfilerCallbackImpl::ExceptionThrown(ObjectID thrownObjectId)
{
    return S_OK;
}


HRESULT STDMETHODCALLTYPE CCorProfilerCallbackImpl::ExceptionSearchFunctionEnter(FunctionID functionId)
{
    return S_OK;
}


HRESULT STDMETHODCALLTYPE CCorProfilerCallbackImpl::ExceptionSearchFunctionLeave(void)
{
    return S_OK;
}


HRESULT STDMETHODCALLTYPE CCorProfilerCallbackImpl::ExceptionSearchFilterEnter(FunctionID functionId)
{
    return S_OK;
}


HRESULT STDMETHODCALLTYPE CCorProfilerCallbackImpl::ExceptionSearchFilterLeave(void)
{
    return S_OK;
}


HRESULT STDMETHODCALLTYPE CCorProfilerCallbackImpl::ExceptionSearchCatcherFound(FunctionID functionId)
{
    return S_OK;
}


HRESULT STDMETHODCALLTYPE CCorProfilerCallbackImpl::ExceptionOSHandlerEnter(UINT_PTR __unused)
{
    return S_OK;
}


HRESULT STDMETHODCALLTYPE CCorProfilerCallbackImpl::ExceptionOSHandlerLeave(UINT_PTR __unused)
{
    return S_OK;
}


HRESULT STDMETHODCALLTYPE CCorProfilerCallbackImpl::ExceptionUnwindFunctionEnter(FunctionID functionId)
{
    return S_OK;
}


HRESULT STDMETHODCALLTYPE CCorProfilerCallbackImpl::ExceptionUnwindFunctionLeave(void)
{
    return S_OK;
}


HRESULT STDMETHODCALLTYPE CCorProfilerCallbackImpl::ExceptionUnwindFinallyEnter(FunctionID functionId)
{
    return S_OK;
}


HRESULT STDMETHODCALLTYPE CCorProfilerCallbackImpl::ExceptionUnwindFinallyLeave(void)
{
    return S_OK;
}


HRESULT STDMETHODCALLTYPE CCorProfilerCallbackImpl::ExceptionCatcherEnter(FunctionID functionId, ObjectID objectId)
{
    return S_OK;
}


HRESULT STDMETHODCALLTYPE CCorProfilerCallbackImpl::ExceptionCatcherLeave(void)
{
    return S_OK;
}


HRESULT STDMETHODCALLTYPE CCorProfilerCallbackImpl::COMClassicVTableCreated(ClassID wrappedClassId, REFGUID implementedIID, void *pVTable, ULONG cSlots)
{
    return S_OK;
}


HRESULT STDMETHODCALLTYPE CCorProfilerCallbackImpl::COMClassicVTableDestroyed(ClassID wrappedClassId, REFGUID implementedIID, void *pVTable)
{
    return S_OK;
}


HRESULT STDMETHODCALLTYPE CCorProfilerCallbackImpl::ExceptionCLRCatcherFound(void)
{
    return S_OK;
}


HRESULT STDMETHODCALLTYPE CCorProfilerCallbackImpl::ExceptionCLRCatcherExecute(void)
{
    return S_OK;
}

// ICorProfilerCallback2
HRESULT STDMETHODCALLTYPE CCorProfilerCallbackImpl::ThreadNameChanged(ThreadID threadId, ULONG cchName, _In_reads_opt_(cchName) WCHAR name[])
{
    return S_OK;
}

HRESULT STDMETHODCALLTYPE CCorProfilerCallbackImpl::GarbageCollectionStarted(int cGenerations, BOOL generationCollected[], COR_PRF_GC_REASON reason)
{
    return S_OK;
}

HRESULT STDMETHODCALLTYPE CCorProfilerCallbackImpl::SurvivingReferences(ULONG cSurvivingObjectIDRanges, ObjectID objectIDRangeStart[], ULONG cObjectIDRangeLength[])
{
    return S_OK;
}

HRESULT STDMETHODCALLTYPE CCorProfilerCallbackImpl::GarbageCollectionFinished(void)
{
    return S_OK;
}

HRESULT STDMETHODCALLTYPE CCorProfilerCallbackImpl::FinalizeableObjectQueued(DWORD finalizerFlags, ObjectID objectID)
{
    return S_OK;
}

HRESULT STDMETHODCALLTYPE CCorProfilerCallbackImpl::RootReferences2(ULONG cRootRefs, ObjectID rootRefIds[], COR_PRF_GC_ROOT_KIND rootKinds[], COR_PRF_GC_ROOT_FLAGS rootFlags[], UINT_PTR rootIds[])
{
    return S_OK;
}

HRESULT STDMETHODCALLTYPE CCorProfilerCallbackImpl::HandleCreated(GCHandleID handleId, ObjectID initialObjectId)
{
    return S_OK;
}

HRESULT STDMETHODCALLTYPE CCorProfilerCallbackImpl::HandleDestroyed(GCHandleID handleId)
{
    return S_OK;
}


// ICorProfiler3
HRESULT STDMETHODCALLTYPE CCorProfilerCallbackImpl::InitializeForAttach(IUnknown *pCorProfilerInfoUnk, void *pvClientData, UINT cbClientData)
{
    return S_OK;
}

HRESULT STDMETHODCALLTYPE CCorProfilerCallbackImpl::ProfilerAttachComplete(void)
{
    return S_OK;
}

HRESULT STDMETHODCALLTYPE CCorProfilerCallbackImpl::ProfilerDetachSucceeded(void)
{
    return S_OK;
}


// ICorProfiler4
HRESULT STDMETHODCALLTYPE CCorProfilerCallbackImpl::ReJITCompilationStarted(FunctionID functionId, ReJITID rejitId, BOOL fIsSafeToBlock)
{
    return S_OK;
}

HRESULT STDMETHODCALLTYPE CCorProfilerCallbackImpl::GetReJITParameters(ModuleID moduleId, mdMethodDef methodId, ICorProfilerFunctionControl *pFunctionControl)
{
    return S_OK;
}

HRESULT STDMETHODCALLTYPE CCorProfilerCallbackImpl::ReJITCompilationFinished(FunctionID functionId, ReJITID rejitId, HRESULT hrStatus, BOOL fIsSafeToBlock)
{
    return S_OK;
}

HRESULT STDMETHODCALLTYPE CCorProfilerCallbackImpl::ReJITError(ModuleID moduleId, mdMethodDef methodId, FunctionID functionId, HRESULT hrStatus)
{
    return S_OK;
}

HRESULT STDMETHODCALLTYPE CCorProfilerCallbackImpl::MovedReferences2(ULONG cMovedObjectIDRanges, ObjectID oldObjectIDRangeStart[], ObjectID newObjectIDRangeStart[], SIZE_T cObjectIDRangeLength[])
{
    return S_OK;
}

HRESULT STDMETHODCALLTYPE CCorProfilerCallbackImpl::SurvivingReferences2(ULONG cSurvivingObjectIDRanges, ObjectID objectIDRangeStart[], SIZE_T cObjectIDRangeLength[])
{
    return S_OK;
}


// ICorProfiler5
HRESULT STDMETHODCALLTYPE CCorProfilerCallbackImpl::ConditionalWeakTableElementReferences(ULONG cRootRefs, ObjectID keyRefIds[], ObjectID valueRefIds[], GCHandleID rootIds[])
{
    return S_OK;
}
