// Profiler.cpp : Implementation of CProfiler

#include "stdafx.h"
#include "Profiler.h"
//#include "MethodInfo.h"

#include <iostream>

DotNetProfiler::CProfiler* g_pICorProfilerCallback;


const int DotNetProfiler::CProfiler::NAME_BUFFER_SIZE = 1024;

typedef struct {
	ThreadID threadId;
	int indent;
} ThreadIndent;

ThreadIndent threads[10];
int threadCount = 0;

ThreadIndent* GetThreadIndent(ThreadID threadId)
{
	for (int i = 0; i < threadCount; i++)
	{
		if (threads[i].threadId == threadId) {
			return &threads[i];
		}
	}

	return 0;
}

HRESULT STDMETHODCALLTYPE DotNetProfiler::CProfiler::ThreadCreated(ThreadID threadId)
{
	HRESULT hr;
	ContextID contextId;

	hr = m_pICorProfilerInfo4->GetThreadContext(threadId, &contextId);

	tracer->trace(L"ThreadCreated {0} {1}", threadId, contextId);
	ThreadIndent threadIndent;
	threadIndent.threadId = threadId;
	threadIndent.indent = 0;
	threads[threadCount++] = threadIndent;
	//m_pICorProfilerInfo4->GetCont

	return hr;
}


extern "C" void EnterNaked3WithInfo(FunctionIDOrClientID, COR_PRF_ELT_INFO);

extern "C" void __stdcall EnterGlobalWithInfo(FunctionIDOrClientID functionIDOrClientID, COR_PRF_ELT_INFO eltInfo)
{
	if (g_pICorProfilerCallback != NULL)
		g_pICorProfilerCallback->Enter3WithInfo(functionIDOrClientID, eltInfo);
}

void DotNetProfiler::CProfiler::Enter3WithInfo(FunctionIDOrClientID functionIDOrClientID, COR_PRF_ELT_INFO eltInfo)
{
	FunctionID functionID = functionIDOrClientID.functionID;

	WCHAR wszMethodName[NAME_BUFFER_SIZE];
	GetFullFunctionName(functionID, wszMethodName);

	ThreadID threadId;
	m_pICorProfilerInfo4->GetCurrentThreadID(&threadId);

	ThreadIndent* indent = GetThreadIndent(threadId);
	tracer->trace(L"Enter {0}{1}", std::string(indent->indent, ' '), wszMethodName);
	//std::wcout << L"Enter " << wszMethodName << std::endl;

	indent->indent++;
	//auto methodInfo = m_methods[functionID];
	//methodInfo->LoadArguments(eltInfo);

	//std::cout << "Enter functionID = " << functionID << " eltInfo = " << eltInfo << std::endl;


}

extern "C" void LeaveNaked3WithInfo(FunctionIDOrClientID functionIDOrClientID, COR_PRF_ELT_INFO eltInfo);

extern "C" void __stdcall LeaveGlobalWithInfo(FunctionIDOrClientID functionIDOrClientID, COR_PRF_ELT_INFO eltInfo)
{
	if (g_pICorProfilerCallback != NULL)
		g_pICorProfilerCallback->Leave3WithInfo(functionIDOrClientID, eltInfo);
}

void DotNetProfiler::CProfiler::Leave3WithInfo(FunctionIDOrClientID functionIDOrClientID, COR_PRF_ELT_INFO eltInfo)
{
	//std::cout << "Leave" << std::endl;

	FunctionID functionID = functionIDOrClientID.functionID;

	WCHAR wszMethodName[NAME_BUFFER_SIZE];
	GetFullFunctionName(functionID, wszMethodName);

	ThreadID threadId;
	m_pICorProfilerInfo4->GetCurrentThreadID(&threadId);

	ThreadIndent* indent = GetThreadIndent(threadId);

	indent->indent--;

	//for (int i = 0; i < indent; i++) {
	//	std::wcout << L" ";
	//}

	//std::wcout << L"Leave " << wszMethodName << std::endl;
	tracer->trace(L"Leave {0}{1}", std::string(indent->indent, ' '), wszMethodName);
}

extern "C" void TailcallNaked3WithInfo(FunctionIDOrClientID functionIDOrClientID, COR_PRF_ELT_INFO eltInfo);

extern "C" void __stdcall TailcallGlobalWithInfo(FunctionIDOrClientID functionIDOrClientID, COR_PRF_ELT_INFO eltInfo)
{
	if (g_pICorProfilerCallback != NULL)
		g_pICorProfilerCallback->Tailcall3WithInfo(functionIDOrClientID, eltInfo);
}



void DotNetProfiler::CProfiler::Tailcall3WithInfo(FunctionIDOrClientID functionIDOrClientID, COR_PRF_ELT_INFO eltInfo)
{
	FunctionID functionID = functionIDOrClientID.functionID;

	WCHAR wszMethodName[NAME_BUFFER_SIZE];
	GetFullFunctionName(functionID, wszMethodName);

	ThreadID threadId;
	m_pICorProfilerInfo4->GetCurrentThreadID(&threadId);

	ThreadIndent* indent = GetThreadIndent(threadId);

	indent->indent--;

	tracer->trace(L"Tailcall {0}{1}", std::string(indent->indent, ' '), wszMethodName);
}

UINT_PTR __stdcall FunctionMapper(FunctionID functionID, void* clientData, BOOL* pbHookFunction)
{
	DotNetProfiler::CProfiler* profiler = (DotNetProfiler::CProfiler*)clientData;
	profiler->MapFunction(functionID, pbHookFunction);

	return functionID;
}

void DotNetProfiler::CProfiler::MapFunction(FunctionID functionID, BOOL* pbHookFunction)
{
	WCHAR wszMethodName[NAME_BUFFER_SIZE];
	GetFullFunctionName(functionID, wszMethodName);

	bool profileFunction = StrCmpNW(wszMethodName, L"TaskRunner", 10) == 0;

	*pbHookFunction = profileFunction;

	//tracer->trace(L"MapFunction {0}: functionID = {1}, hook = {2}", wszMethodName, functionID, *pbHookFunction ? L"true" : L"false");

	//std::wcout << L"CProfiler::MapFunction functionID = " << functionID << std::endl;
	//bool profileFunction = StrCmpNW(wszMethodName, L"TestApplication", 15) == 0;

	//auto methodInfo = std::shared_ptr<CMethodInfo>(new CMethodInfo(functionID, m_pICorProfilerInfo4));
	//bool profileFunction = methodInfo->GetClassName().compare(0, 15, L"TestApplication") == 0;

	//if (profileFunction) {
	//	methodInfo->LoadParameters();

	//	m_methods.insert(std::pair<FunctionID, std::shared_ptr<CMethodInfo>>(functionID, methodInfo));

	//	std::wcout << L"mapped method: " << methodInfo << std::endl;
	//	//wprintf(L"mapped method: %ls\n functionID = %llu\n", wszMethodName, functionID);
	//}

	//*pbHookFunction = profileFunction;



	//std::cout << "Method name: " << wszMethodName << std::endl;

	//if (SUCCEEDED(hr)) {
	//    std::cout << "MapFunction, functionID: " << functionID << " succeded" << std::endl;
	//}
	//else {
	//    std::cout << "MapFunction, functionID: " << functionID << " error" << std::endl;
	//}

}

HRESULT DotNetProfiler::CProfiler::GetFullFunctionName(FunctionID functionID, LPWSTR wszMethodName)
{
	HRESULT hr = S_OK;
	CComPtr<IMetaDataImport2> pMetaDataImport;
	mdMethodDef methodToken = mdTypeDefNil;
	mdTypeDef classToken = mdTypeDefNil;
	WCHAR wszMethod[NAME_BUFFER_SIZE];
	WCHAR wszClass[NAME_BUFFER_SIZE];
	ULONG cchMethod;
	ULONG cchClass;
	PCCOR_SIGNATURE sigBlob = NULL;
	ULONG sigBlobByteCount;

	hr = m_pICorProfilerInfo4->GetTokenAndMetaDataFromFunction(functionID, IID_IMetaDataImport2, (LPUNKNOWN*)&pMetaDataImport, &methodToken);
	if (SUCCEEDED(hr))
	{
		hr = pMetaDataImport->GetMethodProps(methodToken, &classToken, wszMethod, NAME_BUFFER_SIZE, &cchMethod, NULL, &sigBlob, &sigBlobByteCount, NULL, NULL);

		if (SUCCEEDED(hr))
		{
			hr = pMetaDataImport->GetTypeDefProps(classToken, wszClass, NAME_BUFFER_SIZE, &cchClass, NULL, NULL);
			if (SUCCEEDED(hr)) {
				_snwprintf_s(wszMethodName, NAME_BUFFER_SIZE, NAME_BUFFER_SIZE, L"%s.%s", wszClass, wszMethod);
			}
		}
	}

	//pMetaDataImport->Release();
	return hr;
}

HRESULT STDMETHODCALLTYPE DotNetProfiler::CProfiler::Initialize(IUnknown *pICorProfilerInfoUnk)
{
	HRESULT hr;

	logger = spdlog::stdout_color_mt("console");

	logger->info(L"started profiler");

	tracer = spdlog::stdout_color_mt("tracer");
	tracer->set_level(spdlog::level::trace);
	tracer->set_pattern("%t\t %v");

	hr = pICorProfilerInfoUnk->QueryInterface(IID_ICorProfilerInfo, (LPVOID*)&m_pICorProfilerInfo);
	if (FAILED(hr))
	{
		return E_FAIL;
	}

	hr = pICorProfilerInfoUnk->QueryInterface(IID_ICorProfilerInfo2, (LPVOID*)&m_pICorProfilerInfo2);
	if (FAILED(hr))
	{
		return E_FAIL;
	}

	hr = pICorProfilerInfoUnk->QueryInterface(IID_ICorProfilerInfo3, (LPVOID*)&m_pICorProfilerInfo3);
	if (FAILED(hr))
	{
		return E_FAIL;
	}

	hr = pICorProfilerInfoUnk->QueryInterface(IID_ICorProfilerInfo4, (LPVOID*)&m_pICorProfilerInfo4);
	if (FAILED(hr))
	{
		return E_FAIL;
	}

	hr = pICorProfilerInfoUnk->QueryInterface(IID_ICorProfilerInfo5, (LPVOID*)&m_pICorProfilerInfo5);
	if (FAILED(hr))
	{
		return E_FAIL;
	}

	hr = pICorProfilerInfoUnk->QueryInterface(IID_ICorProfilerInfo6, (LPVOID*)&m_pICorProfilerInfo6);
	if (FAILED(hr))
	{
		return E_FAIL;
	}

	hr = pICorProfilerInfoUnk->QueryInterface(IID_ICorProfilerInfo7, (LPVOID*)&m_pICorProfilerInfo7);
	if (FAILED(hr))
	{
		return E_FAIL;
	}

	hr = pICorProfilerInfoUnk->QueryInterface(IID_ICorProfilerInfo8, (LPVOID*)&m_pICorProfilerInfo8);
	if (FAILED(hr))
	{
		return E_FAIL;
	}

	SetEventMasks();

	hr = m_pICorProfilerInfo3->SetEnterLeaveFunctionHooks3WithInfo((FunctionEnter3WithInfo*)EnterNaked3WithInfo, (FunctionLeave3WithInfo*)LeaveNaked3WithInfo, (FunctionTailcall3WithInfo*)TailcallNaked3WithInfo);
	if (FAILED(hr))
	{
		return E_FAIL;
	}

	hr = m_pICorProfilerInfo3->SetFunctionIDMapper2(FunctionMapper, (LPVOID)this);
	if (FAILED(hr))
	{
		return E_FAIL;
	}


	g_pICorProfilerCallback = this;
	return S_OK;
}


HRESULT STDMETHODCALLTYPE DotNetProfiler::CProfiler::Shutdown(void)
{
	return S_OK;
}

void DotNetProfiler::CProfiler::SetEventMasks()
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

	m_pICorProfilerInfo4->SetEventMask((DWORD)COR_PRF_MONITOR_ENTERLEAVE | COR_PRF_ENABLE_FUNCTION_ARGS | COR_PRF_ENABLE_FUNCTION_RETVAL | COR_PRF_ENABLE_FRAME_INFO | COR_PRF_MONITOR_THREADS);
}

// CProfiler

