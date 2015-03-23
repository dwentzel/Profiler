#pragma once

#include "stdafx.h"

#include <memory>
#include <string>

#include <cor.h>
#include <corprof.h>

namespace ClrProfiler {

    class CParameterInfo
    {
    public:
        static CParameterInfo ParseFromSignature(PCCOR_SIGNATURE& signature, ATL::CComPtr<IMetaDataImport2> pMetaDataImport2);

        CParameterInfo();
        ~CParameterInfo();

    private:
        CorElementType m_elementType;
        bool m_isPtr{ false };
        bool m_isByref{ false };
        bool m_isClass{ false };

        static bool ParseSignatureElement(CParameterInfo& parameterInfo, PCCOR_SIGNATURE& pcSignature, ATL::CComPtr<IMetaDataImport2> pMetadataImport2);
        static std::unique_ptr<WCHAR[]> GetTypeName(PCCOR_SIGNATURE& pcSignature, ATL::CComPtr<IMetaDataImport2> pMetaDataImport2);

        static LPWSTR ElementTypeToString(CorElementType elementType);

        friend std::wostream& operator<<(std::wostream& out, const CParameterInfo& parameterInfo);
    };

    std::wostream& operator<<(std::wostream& out, const CParameterInfo& parameterInfo);
}