#pragma once

#include "stdafx.h"

#include "ParameterInfo.h"

#include <vector>

#include <cor.h>
#include <corprof.h>

namespace ClrProfiler {

    class CMethodInfo
    {
    public:
        CMethodInfo(FunctionID functionID, ATL::CComPtr<ICorProfilerInfo4> pICorProfilerInfo4);
        ~CMethodInfo();

        //void LoadMethodName(FunctionID functionID);
        void LoadParameters();
        void LoadArguments(COR_PRF_ELT_INFO eltInfo);

        ULONG GetCchClassName() const;

        LPWSTR const GetClassName() const;
        LPWSTR const GetMethodName() const;

    private:
        bool HasThis() const;
        bool IsGeneric() const;
        bool IsVararg() const;
        bool HasExplicitThis() const;

        std::vector<std::unique_ptr<CParameterInfo>>::const_iterator begin() const;
        std::vector<std::unique_ptr<CParameterInfo>>::const_iterator end() const;

    private:
        FunctionID m_functionID;
        ATL::CComPtr<ICorProfilerInfo4> m_pICorProfilerInfo4;
        ATL::CComPtr<IMetaDataImport2> m_pMetaDataImport2;

        mdTypeDef m_classDefToken{ mdTypeDefNil };
        mdMethodDef m_methodDefToken{ mdMethodDefNil };

        PCCOR_SIGNATURE m_pcSignature{ NULL };
        ULONG m_signatureByteCount{ 0 };
        ULONG m_callingConvention{ 0 };
        CorElementType m_returnType;

        ULONG m_cchMethodName;
        ULONG m_cchClassName;

        LPWSTR m_methodName;
        LPWSTR m_className;

        std::vector<std::unique_ptr<CParameterInfo>> m_parameters;

        friend std::wostream& operator<<(std::wostream& out, const CMethodInfo& methodInfo);
    };

    inline ULONG CMethodInfo::GetCchClassName() const
    {
        return m_cchClassName;
    }

    inline LPWSTR const CMethodInfo::GetClassName() const
    {
        return m_className;
    }

    inline LPWSTR const CMethodInfo::GetMethodName() const
    {
        return m_methodName;
    }

    inline std::vector<std::unique_ptr<CParameterInfo>>::const_iterator CMethodInfo::begin() const
    {
        return m_parameters.begin();
    }

    inline std::vector<std::unique_ptr<CParameterInfo>>::const_iterator CMethodInfo::end() const
    {
        return m_parameters.end();
    }

    inline bool CMethodInfo::HasThis() const
    {
        return (m_callingConvention & 0x20) == 0x20;
    }

    inline bool CMethodInfo::IsGeneric() const
    {
        return (m_callingConvention & 0x10) == 0x10;
    }

    inline bool CMethodInfo::IsVararg() const
    {
        return (m_callingConvention & 0x05) == 0x05;
    }

    inline bool CMethodInfo::HasExplicitThis() const
    {
        return (m_callingConvention & 0x40) == 0x40;
    }


    std::wostream& operator<<(std::wostream& out, const CMethodInfo& methodInfo);
}