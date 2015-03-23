#include "stdafx.h"
#include "MethodInfo.h"
#include "ParameterInfo.h"

#include <iostream>
#include <vector>

ClrProfiler::CMethodInfo::CMethodInfo(FunctionID functionID, ATL::CComPtr<ICorProfilerInfo4> pICorProfilerInfo4)
    : m_functionID{ functionID }, m_pICorProfilerInfo4{ pICorProfilerInfo4 }
{
    HRESULT hr;

    WCHAR nameBuffer[NAME_BUFFER_SIZE];
    ULONG nameBufferCharCount;
    //WCHAR classNameBuffer[NAME_BUFFER_SIZE];
    //ULONG methodNameCharCount;
    //ULONG classNameCharCount;


    hr = m_pICorProfilerInfo4->GetTokenAndMetaDataFromFunction(m_functionID, IID_IMetaDataImport2, (LPUNKNOWN*)&m_pMetaDataImport2, &m_methodDefToken);
    hr = m_pMetaDataImport2->GetMethodProps(m_methodDefToken, &m_classDefToken, nameBuffer, NAME_BUFFER_SIZE, &nameBufferCharCount, NULL, &m_pcSignature, &m_signatureByteCount, NULL, NULL);
    m_methodName = std::wstring(nameBuffer, nameBufferCharCount - 1);
    
    hr = m_pMetaDataImport2->GetTypeDefProps(m_classDefToken, nameBuffer, NAME_BUFFER_SIZE, &nameBufferCharCount, NULL, NULL);
    m_className = std::wstring(nameBuffer, nameBufferCharCount - 1);


    //hr = m_pMetaDataImport2->GetTypeDefProps(classToken, wszClass, NAME_BUFFER_SIZE, &cchClass, NULL, NULL);
    //if (SUCCEEDED(hr)) {
    //    _snwprintf_s(wszMethodName, NAME_BUFFER_SIZE, NAME_BUFFER_SIZE, L"%s.%s", wszClass, wszMethod);
    //}

    //bool profileFunction = StrCmpNW(wszMethodName, L"TestApplication", 15) == 0;
    //if (!profileFunction) {
    //    return hr;
    //}


}

ClrProfiler::CMethodInfo::~CMethodInfo()
{
}

namespace ClrProfiler{
    std::wostream& operator<<(std::wostream& out, const ClrProfiler::CMethodInfo& methodInfo) 
    {
        out << methodInfo.m_className << L"." << methodInfo.m_methodName << L"(";
        
        bool isFirstParameter{ true };
        for (auto parameter : methodInfo.m_parameters) {
            if (!isFirstParameter) {
                out << L", ";
            }
            else {
                isFirstParameter = false;
            }

            out << parameter;
        }
        out << L")";
        return out;
    }
}

//void ClrProfiler::CMethodInfo::LoadMethodName(FunctionID functionID)
//{
//    HRESULT hr = S_OK;
//    //ATL::CComPtr<IMetaDataImport2> pMetaDataImport;
//    //mdMethodDef methodToken = mdTypeDefNil;
//    mdTypeDef classToken = mdTypeDefNil;
//    WCHAR methodName[NAME_BUFFER_SIZE];
//    WCHAR className[NAME_BUFFER_SIZE];
//    ULONG cchMethod;
//    ULONG cchClass;
//    PCCOR_SIGNATURE sigBlob = NULL;
//    ULONG sigBlobByteCount;
//
//    //hr = m_pICorProfilerInfo4->GetTokenAndMetaDataFromFunction(functionID, IID_IMetaDataImport2, (LPUNKNOWN*)&pMetaDataImport, &methodToken);
//    //if (SUCCEEDED(hr))
//    //{
//        hr = pMetaDataImport->GetMethodProps(methodToken, &classToken, methodName, NAME_BUFFER_SIZE, &cchMethod, NULL, &sigBlob, &sigBlobByteCount, NULL, NULL);
//
//        if (SUCCEEDED(hr))
//        {
//            hr = pMetaDataImport->GetTypeDefProps(classToken, className, NAME_BUFFER_SIZE, &cchClass, NULL, NULL);
//            if (SUCCEEDED(hr)) {
//                _snwprintf_s(wszMethodName, NAME_BUFFER_SIZE, NAME_BUFFER_SIZE, L"%s.%s", className, methodName);
//            }
//        }
//    //}
//
//}

void ClrProfiler::CMethodInfo::LoadParameters() 
{
    PCCOR_SIGNATURE pcCurrentSignature = m_pcSignature;

    ULONG genericArgCount;
    ULONG argCount;

    m_callingConvention = CorSigUncompressCallingConv(pcCurrentSignature);

    if (IsGeneric()) {
        genericArgCount = CorSigUncompressData(pcCurrentSignature);
    }

    argCount = CorSigUncompressData(pcCurrentSignature);
    m_returnType = CorSigUncompressElementType(pcCurrentSignature);


    // this is wrong: byref is a token but not an arg, and should not count agains argCount
    for (int i = 0; i < argCount; i++) {
        auto parameterInfo = CParameterInfo::ParseFromSignature(pcCurrentSignature, m_pMetaDataImport2);
        m_parameters.push_back(parameterInfo);
    }
}

void ClrProfiler::CMethodInfo::LoadArguments(COR_PRF_ELT_INFO eltInfo)
{
    COR_PRF_FRAME_INFO frameInfo;
    ULONG cbArgumentInfo = 0;
    COR_PRF_FUNCTION_ARGUMENT_INFO* pArgumentInfo = NULL;

    HRESULT hr = m_pICorProfilerInfo4->GetFunctionEnter3Info(m_functionID, eltInfo, &frameInfo, &cbArgumentInfo, pArgumentInfo);
    if (hr == HRESULT_FROM_WIN32(ERROR_INSUFFICIENT_BUFFER))
    {
        pArgumentInfo = (COR_PRF_FUNCTION_ARGUMENT_INFO*)malloc(cbArgumentInfo);
        hr = m_pICorProfilerInfo4->GetFunctionEnter3Info(m_functionID, eltInfo, &frameInfo, &cbArgumentInfo, pArgumentInfo);

        std::cout << " pArgumentInfo->numRanges: " << pArgumentInfo->numRanges << std::endl;

        ULONG stringLengthOffset, bufferOffset;
        hr = m_pICorProfilerInfo4->GetStringLayout2(&stringLengthOffset, &bufferOffset);


        bool enableStringInfo = true;
        for (ULONG i = 0; i < pArgumentInfo->numRanges; ++i)
        {
            COR_PRF_FUNCTION_ARGUMENT_RANGE argumentRange = pArgumentInfo->ranges[i];

            if (argumentRange.length == 0)
            {
                continue;
            }
            ObjectID* id = reinterpret_cast<ObjectID*>(argumentRange.startAddress);

            printf(" id = %x\n", id);
            ULONG size = 0;

            std::cout << " argumentRange.length == " << argumentRange.length << std::endl;

            if (enableStringInfo) {
                DWORD stringLen = 0;
                UINT_PTR* tp = reinterpret_cast<UINT_PTR*>(id);



                //DWORD64 stringOID;
                //LPVOID arg = (LPVOID)malloc(argumentRange.length);
                DWORD64 stringLength;
                LPWSTR tempString = (LPWSTR)malloc(NAME_BUFFER_SIZE);
                //memcpy(&stringOID, ((const void *)(argumentRange.startAddress)), argumentRange.length);
                //memcpy(&stringOID, ((const void *)(argumentRange.startAddress)), 4);
                //memcpy(arg, ((const void *)(argumentRange.startAddress)), argumentRange.length);
                //memcpy(&stringLength, ((const void *)(arg + stringLengthOffset)), sizeof(ULONG));
                //memcpy(tempString, ((const void *)(stringOID + bufferOffset)), stringLength * sizeof(DWORD));

                //wprintf(L" arg: %s\n", arg);

                //free(arg);
                free(tempString);
                //tempString[stringLength * sizeof(DWORD)] = '\0'; 
                //LOG4CXX_DEBUG(myMainLogger, tempString);

                //UINT stringLen = *(tp + stringLengthOffset);
                //LOG4CXX_DEBUG(myMainLogger, "len = " << stringLength)
            }
            //if (*id == 0x1000) {
            //    enableStringInfo = true;
            //}
        }

        free(pArgumentInfo);
    }

    if (FAILED(hr))
    {
        if (hr == HRESULT_FROM_WIN32(ERROR_INSUFFICIENT_BUFFER))
        {
            std::cout << " ERROR_INSUFFICIENT_BUFFER " << std::endl;
        }

        if (hr == E_INVALIDARG)
        {
            std::cout << " INVALID ARGUMENT" << std::endl;
        }

        std::cout << " GetFunctionEnter3Info failed hr = " << std::hex << hr << std::dec << std::endl;
    }

    //_ASSERTE(pArgumentInfo);


    std::cout << " cbArgumentInfo = " << cbArgumentInfo << std::endl;
}