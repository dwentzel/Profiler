#pragma once



class CCorProfilerCallbackImpl : public ICorProfilerCallback5
{
public:
    CCorProfilerCallbackImpl();
    ~CCorProfilerCallbackImpl();

    STDMETHOD(Initialize)(IUnknown *pICorProfilerInfoUnk);
    STDMETHOD(Shutdown)(void);

    STDMETHOD(AppDomainCreationStarted)(AppDomainID appDomainId);
    STDMETHOD(AppDomainCreationFinished)(AppDomainID appDomainId, HRESULT hrStatus);
    STDMETHOD(AppDomainShutdownStarted)(AppDomainID appDomainId);
    STDMETHOD(AppDomainShutdownFinished)(AppDomainID appDomainId, HRESULT hrStatus);

    STDMETHOD(AssemblyLoadStarted)(AssemblyID assemblyId);
    STDMETHOD(AssemblyLoadFinished)(AssemblyID assemblyId, HRESULT hrStatus);
    STDMETHOD(AssemblyUnloadStarted)(AssemblyID assemblyId);
    STDMETHOD(AssemblyUnloadFinished)(AssemblyID assemblyId, HRESULT hrStatus);

    STDMETHOD(ModuleLoadStarted)(ModuleID moduleId);
    STDMETHOD(ModuleLoadFinished)(ModuleID moduleId, HRESULT hrStatus);
    STDMETHOD(ModuleUnloadStarted)(ModuleID moduleId);
    STDMETHOD(ModuleUnloadFinished)(ModuleID moduleId, HRESULT hrStatus);
    STDMETHOD(ModuleAttachedToAssembly)(ModuleID moduleId, AssemblyID AssemblyId);

    STDMETHOD(ClassLoadStarted)(ClassID classId);
    STDMETHOD(ClassLoadFinished)(ClassID classId, HRESULT hrStatus);
    STDMETHOD(ClassUnloadStarted)(ClassID classId);
    STDMETHOD(ClassUnloadFinished)(ClassID classId, HRESULT hrStatus);

    STDMETHOD(FunctionUnloadStarted)(FunctionID functionId);

    STDMETHOD(JITCompilationStarted)(FunctionID functionId, BOOL fIsSafeToBlock);
    STDMETHOD(JITCompilationFinished)(FunctionID functionId, HRESULT hrStatus, BOOL fIsSafeToBlock);
    STDMETHOD(JITCachedFunctionSearchStarted)(FunctionID functionId, BOOL *pbUseCachedFunction);
    STDMETHOD(JITCachedFunctionSearchFinished)(FunctionID functionId, COR_PRF_JIT_CACHE result);
    STDMETHOD(JITFunctionPitched)(FunctionID functionId);
    STDMETHOD(JITInlining)(FunctionID callerId, FunctionID calleeId, BOOL *pfShouldInline);

    STDMETHOD(ThreadCreated)(ThreadID threadId);
    STDMETHOD(ThreadDestroyed)(ThreadID threadId);
    STDMETHOD(ThreadAssignedToOSThread)(ThreadID managedThreadId, DWORD osThreadId);

    STDMETHOD(RemotingClientInvocationStarted)(void);
    STDMETHOD(RemotingClientSendingMessage)(GUID *pCookie, BOOL fIsAsync);
    STDMETHOD(RemotingClientReceivingReply)(GUID *pCookie, BOOL fIsAsync);
    STDMETHOD(RemotingClientInvocationFinished)(void);
    STDMETHOD(RemotingServerReceivingMessage)(GUID *pCookie, BOOL fIsAsync);
    STDMETHOD(RemotingServerInvocationStarted)(void);
    STDMETHOD(RemotingServerInvocationReturned)(void);
    STDMETHOD(RemotingServerSendingReply)(GUID *pCookie, BOOL fIsAsync);

    STDMETHOD(UnmanagedToManagedTransition)(FunctionID functionId, COR_PRF_TRANSITION_REASON reason);
    STDMETHOD(ManagedToUnmanagedTransition)(FunctionID functionId, COR_PRF_TRANSITION_REASON reason);

    STDMETHOD(RuntimeSuspendStarted)(COR_PRF_SUSPEND_REASON suspendReason);
    STDMETHOD(RuntimeSuspendFinished)(void);
    STDMETHOD(RuntimeSuspendAborted)(void);
    STDMETHOD(RuntimeResumeStarted)(void);
    STDMETHOD(RuntimeResumeFinished)(void);
    STDMETHOD(RuntimeThreadSuspended)(ThreadID threadId);
    STDMETHOD(RuntimeThreadResumed)(ThreadID threadId);

    STDMETHOD(MovedReferences)(ULONG cMovedObjectIDRanges, ObjectID oldObjectIDRangeStart[], ObjectID newObjectIDRangeStart[], ULONG cObjectIDRangeLength[]);
    STDMETHOD(ObjectAllocated)(ObjectID objectId, ClassID classId);
    STDMETHOD(ObjectsAllocatedByClass)(ULONG cClassCount, ClassID classIds[], ULONG cObjects[]);
    STDMETHOD(ObjectReferences)(ObjectID objectId, ClassID classId, ULONG cObjectRefs, ObjectID objectRefIds[]);
    STDMETHOD(RootReferences)(ULONG cRootRefs, ObjectID rootRefIds[]);

    STDMETHOD(ExceptionThrown)(ObjectID thrownObjectId);
    STDMETHOD(ExceptionSearchFunctionEnter)(FunctionID functionId);
    STDMETHOD(ExceptionSearchFunctionLeave)(void);
    STDMETHOD(ExceptionSearchFilterEnter)(FunctionID functionId);
    STDMETHOD(ExceptionSearchFilterLeave)(void);
    STDMETHOD(ExceptionSearchCatcherFound)(FunctionID functionId);
    STDMETHOD(ExceptionOSHandlerEnter)(UINT_PTR __unused);
    STDMETHOD(ExceptionOSHandlerLeave)(UINT_PTR __unused);
    STDMETHOD(ExceptionUnwindFunctionEnter)(FunctionID functionId);
    STDMETHOD(ExceptionUnwindFunctionLeave)(void);
    STDMETHOD(ExceptionUnwindFinallyEnter)(FunctionID functionId);
    STDMETHOD(ExceptionUnwindFinallyLeave)(void);
    STDMETHOD(ExceptionCatcherEnter)(FunctionID functionId, ObjectID objectId);
    STDMETHOD(ExceptionCatcherLeave)(void);
    STDMETHOD(COMClassicVTableCreated)(ClassID wrappedClassId, REFGUID implementedIID, void *pVTable, ULONG cSlots);
    STDMETHOD(COMClassicVTableDestroyed)(ClassID wrappedClassId, REFGUID implementedIID, void *pVTable);
    STDMETHOD(ExceptionCLRCatcherFound)(void);
    STDMETHOD(ExceptionCLRCatcherExecute)(void);


    // ICorProfilerCallback2
    STDMETHOD(ThreadNameChanged)(ThreadID threadId, ULONG cchName, _In_reads_opt_(cchName)  WCHAR name[]);
    STDMETHOD(GarbageCollectionStarted)(int cGenerations, BOOL generationCollected[], COR_PRF_GC_REASON reason);
    STDMETHOD(SurvivingReferences)(ULONG cSurvivingObjectIDRanges, ObjectID objectIDRangeStart[], ULONG cObjectIDRangeLength[]);
    STDMETHOD(GarbageCollectionFinished)(void);
    STDMETHOD(FinalizeableObjectQueued)(DWORD finalizerFlags, ObjectID objectID);
    STDMETHOD(RootReferences2)(ULONG cRootRefs, ObjectID rootRefIds[], COR_PRF_GC_ROOT_KIND rootKinds[], COR_PRF_GC_ROOT_FLAGS rootFlags[], UINT_PTR rootIds[]);
    STDMETHOD(HandleCreated)(GCHandleID handleId, ObjectID initialObjectId);
    STDMETHOD(HandleDestroyed)(GCHandleID handleId);

    // ICorProfiler3
    STDMETHOD(InitializeForAttach)(IUnknown *pCorProfilerInfoUnk, void *pvClientData, UINT cbClientData);
    STDMETHOD(ProfilerAttachComplete)(void);
    STDMETHOD(ProfilerDetachSucceeded)(void);

    // ICorProfiler4
    STDMETHOD(ReJITCompilationStarted)(FunctionID functionId, ReJITID rejitId, BOOL fIsSafeToBlock);
    STDMETHOD(GetReJITParameters)(ModuleID moduleId, mdMethodDef methodId, ICorProfilerFunctionControl *pFunctionControl);
    STDMETHOD(ReJITCompilationFinished)(FunctionID functionId, ReJITID rejitId, HRESULT hrStatus, BOOL fIsSafeToBlock);
    STDMETHOD(ReJITError)(ModuleID moduleId, mdMethodDef methodId, FunctionID functionId, HRESULT hrStatus);
    STDMETHOD(MovedReferences2)(ULONG cMovedObjectIDRanges, ObjectID oldObjectIDRangeStart[], ObjectID newObjectIDRangeStart[], SIZE_T cObjectIDRangeLength[]);
    STDMETHOD(SurvivingReferences2)(ULONG cSurvivingObjectIDRanges, ObjectID objectIDRangeStart[], SIZE_T cObjectIDRangeLength[]);

    // ICorProfiler5
    STDMETHOD(ConditionalWeakTableElementReferences)(ULONG cRootRefs, ObjectID keyRefIds[], ObjectID valueRefIds[], GCHandleID rootIds[]);

};

