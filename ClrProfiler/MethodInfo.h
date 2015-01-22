#pragma once

#include "stdafx.h"

#include <cor.h>
#include <corprof.h>

class CMethodInfo
{
public:
    CMethodInfo(FunctionID functionID, ATL::CComPtr<ICorProfilerInfo4> pICorProfilerInfo4);
    ~CMethodInfo();

    void GetArguments(COR_PRF_ELT_INFO eltInfo);

private:
    FunctionID m_functionID;
    ATL::CComPtr<ICorProfilerInfo4> m_pICorProfilerInfo4;
    ATL::CComPtr<IMetaDataImport2> m_pMetaDataImport2;

    mdTypeDef m_classDefToken{ mdTypeDefNil };
    mdMethodDef m_methodDefToken{ mdTypeDefNil };

    PCCOR_SIGNATURE m_pcSignature{ NULL };
    ULONG m_signatureByteCount{ 0 };
};

