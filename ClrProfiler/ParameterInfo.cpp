#include "stdafx.h"
#include "ParameterInfo.h"

#include <memory>

#include <strsafe.h>


ClrProfiler::CParameterInfo::CParameterInfo()
{
}


ClrProfiler::CParameterInfo::~CParameterInfo()
{
}

ClrProfiler::CParameterInfo ClrProfiler::CParameterInfo::ParseFromSignature(PCCOR_SIGNATURE& pcSignature, ATL::CComPtr<IMetaDataImport2> pMetaDataImport2)
{
    CParameterInfo parameterInfo;
    bool done = false;
    while (!done) {
        done = ParseSignatureElement(parameterInfo, pcSignature, pMetaDataImport2);
    }

    return parameterInfo;
}

bool ClrProfiler::CParameterInfo::ParseSignatureElement(CParameterInfo& parameterInfo, PCCOR_SIGNATURE& pcSignature, ATL::CComPtr<IMetaDataImport2> pMetaDataImport2)
{
    CorElementType elementType = CorSigUncompressElementType(pcSignature);

    if (elementType == ELEMENT_TYPE_VALUETYPE || elementType == ELEMENT_TYPE_CLASS) {
        auto className = GetTypeName(pcSignature, pMetaDataImport2);
        parameterInfo.m_elementType = elementType;
        parameterInfo.m_isClass = true;

        //wprintf(L"%x (%s) ", elementType, className);
    }
    else if (elementType == ELEMENT_TYPE_BYREF)
    {
        parameterInfo.m_isByref = true;
        return false;
    }
    else if (elementType == ELEMENT_TYPE_PTR) {
        parameterInfo.m_isPtr = true;
        return false;
    }
    else {
        parameterInfo.m_elementType = elementType;
        //wprintf(L"%x (%s) ", elementType, ElementTypeToString(elementType));
    }

    return true;
}

std::unique_ptr<WCHAR[]> ClrProfiler::CParameterInfo::GetTypeName(PCCOR_SIGNATURE& pcSignature, ATL::CComPtr<IMetaDataImport2> pMetaDataImport2)
{
    HRESULT hr;
    ULONG cchName;
    mdToken token = CorSigUncompressToken(pcSignature);

    WCHAR className[NAME_BUFFER_SIZE];
    if (TypeFromToken(token) == mdtTypeRef) {
        hr = pMetaDataImport2->GetTypeRefProps(token, NULL, className, NAME_BUFFER_SIZE, &cchName);
    }
    else {
        hr = pMetaDataImport2->GetTypeDefProps(token, className, NAME_BUFFER_SIZE, &cchName, NULL, NULL);
    }

    WCHAR *cn = new WCHAR[cchName];

    StringCchCopy(cn, cchName, className);

    return std::unique_ptr<WCHAR[]>(cn);
}

LPWSTR ClrProfiler::CParameterInfo::ElementTypeToString(CorElementType elementType)
{
    switch (elementType) {
    case ELEMENT_TYPE_END:
        break;
    case ELEMENT_TYPE_VOID:
        return L"void";
    case ELEMENT_TYPE_BOOLEAN:
        return L"bool";
    case ELEMENT_TYPE_CHAR:
        return L"char";
    case ELEMENT_TYPE_I1:
        return L"byte";
    case ELEMENT_TYPE_U1:
        return L"unsigned byte";
    case ELEMENT_TYPE_I2:
        return L"short";
    case ELEMENT_TYPE_U2:
        return L"unsigned short";
    case ELEMENT_TYPE_I4:
        return L"int";
    case ELEMENT_TYPE_U4:
        return L"unsigned int";
    case ELEMENT_TYPE_I8:
        return L"long";
    case ELEMENT_TYPE_U8:
        return L"unsigned long";
    case ELEMENT_TYPE_R4:
        return L"float";
    case ELEMENT_TYPE_R8:
        return L"double";
    case ELEMENT_TYPE_STRING:
        return L"string";

    case ELEMENT_TYPE_I:     // native integer size
        return L"native int";
    case ELEMENT_TYPE_U:     // native unsigned integer size
        return L"native uint";

        // every type above PTR will be simple type
    case ELEMENT_TYPE_PTR:     // PTR <type>
    case ELEMENT_TYPE_BYREF:     // BYREF <type>

        // Please use ELEMENT_TYPE_VALUETYPE. ELEMENT_TYPE_VALUECLASS is deprecated.
    case ELEMENT_TYPE_VALUETYPE:     // VALUETYPE <class Token>
    case ELEMENT_TYPE_CLASS:     // CLASS <class Token>
    case ELEMENT_TYPE_VAR:     // a class type variable VAR <number>
    case ELEMENT_TYPE_ARRAY:     // MDARRAY <type> <rank> <bcount> <bound1> ... <lbcount> <lb1> ...
    case ELEMENT_TYPE_GENERICINST:     // GENERICINST <generic type> <argCnt> <arg1> ... <argn>
    case ELEMENT_TYPE_TYPEDBYREF:     // TYPEDREF  (it takes no args) a typed referece to some other type


    case ELEMENT_TYPE_FNPTR:     // FNPTR <complete sig for the function including calling convention>
    case ELEMENT_TYPE_OBJECT:     // Shortcut for System.Object
    case ELEMENT_TYPE_SZARRAY:     // Shortcut for single dimension zero lower bound array
        // SZARRAY <type>
    case ELEMENT_TYPE_MVAR:     // a method type variable MVAR <number>

        // This is only for binding
    case ELEMENT_TYPE_CMOD_REQD:     // required C modifier : E_T_CMOD_REQD <mdTypeRef/mdTypeDef>
    case ELEMENT_TYPE_CMOD_OPT:     // optional C modifier : E_T_CMOD_OPT <mdTypeRef/mdTypeDef>

        // This is for signatures generated internally (which will not be persisted in any way).
    case ELEMENT_TYPE_INTERNAL:     // INTERNAL <typehandle>

        // Note that this is the max of base type excluding modifiers
    case ELEMENT_TYPE_MAX:     // first invalid element type

        return L"";
    }
}

namespace ClrProfiler {
    std::wostream& operator<<(std::wostream& out, const CParameterInfo& parameterInfo)
    {
        if (parameterInfo.m_isByref) {
            out << L"byref ";
        }
        if (parameterInfo.m_isPtr) {
            out << L"ptr ";
        }

        out << CParameterInfo::ElementTypeToString(parameterInfo.m_elementType);
        return out;
    }
}