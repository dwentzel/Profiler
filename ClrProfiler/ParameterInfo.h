#pragma once

#include "stdafx.h"

#include <string>

#include <cor.h>
#include <corprof.h>

namespace ClrProfiler {

    class CParameterInfo
    {
    public:
        static std::unique_ptr<ClrProfiler::CParameterInfo> ParseFromSignature(PCCOR_SIGNATURE& signature, ATL::CComPtr<IMetaDataImport2> pMetaDataImport2);

        ~CParameterInfo();

	private:
		CParameterInfo();

		CParameterInfo(CParameterInfo const&) = delete;
		CParameterInfo& operator=(CParameterInfo const&) = delete;

    private:
        CorElementType m_elementType;
        bool m_isPtr{ false };
        bool m_isByref{ false };
        bool m_isClass{ false };
		bool m_isArray{ false };

		LPWSTR m_className;

        void ParseSignatureElement(PCCOR_SIGNATURE& pcSignature, ATL::CComPtr<IMetaDataImport2> pMetadataImport2);
        static LPWSTR GetTypeName(PCCOR_SIGNATURE& pcSignature, ATL::CComPtr<IMetaDataImport2> pMetaDataImport2);

        static LPWSTR ElementTypeToString(CorElementType elementType);

        friend std::wostream& operator<<(std::wostream& out, CParameterInfo const& parameterInfo);
    };

    std::wostream& operator<<(std::wostream& out, CParameterInfo const& parameterInfo);
}