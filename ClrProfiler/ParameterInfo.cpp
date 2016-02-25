#include "stdafx.h"
#include "ParameterInfo.h"

ClrProfiler::CParameterInfo::CParameterInfo()
{
}


ClrProfiler::CParameterInfo::~CParameterInfo()
{
    delete m_className;
}

std::unique_ptr<ClrProfiler::CParameterInfo> ClrProfiler::CParameterInfo::ParseFromSignature(PCCOR_SIGNATURE& pcSignature, ATL::CComPtr<IMetaDataImport2> pMetaDataImport2)
{
    CParameterInfo* parameterInfo = new CParameterInfo();

    parameterInfo->ParseSignatureElement(pcSignature, pMetaDataImport2);

    return std::unique_ptr<CParameterInfo>(parameterInfo);
}

void ClrProfiler::CParameterInfo::ParseElementType(PCCOR_SIGNATURE& pcSignature, ATL::CComPtr<IMetaDataImport2> pMetaDataImport2)
{
    CorElementType elementType = CorSigUncompressElementType(pcSignature);

    m_elementType = elementType;

    switch (elementType) {
    case ELEMENT_TYPE_VALUETYPE:
    case ELEMENT_TYPE_CLASS:
        m_isClass = true;
        m_className = GetTypeName(pcSignature, pMetaDataImport2);
        break;
    case ELEMENT_TYPE_BYREF:
        m_isByref = true;
        break;
    case ELEMENT_TYPE_PTR:
        m_isPtr = true;
        break;
    case ELEMENT_TYPE_SZARRAY:
        m_isArray = true;
        break;

    }
}

void ClrProfiler::CParameterInfo::ParseSignatureElement(PCCOR_SIGNATURE& pcSignature, ATL::CComPtr<IMetaDataImport2> pMetaDataImport2)
{
    CorElementType elementType = CorSigUncompressElementType(pcSignature);

    if (elementType == ELEMENT_TYPE_VALUETYPE || elementType == ELEMENT_TYPE_CLASS) {
        m_className = GetTypeName(pcSignature, pMetaDataImport2);
        m_elementType = elementType;
        m_isClass = true;

        //wprintf(L"%x (%s) ", elementType, className);
    }
    else if (elementType == ELEMENT_TYPE_BYREF)
    {
        m_isByref = true;
        ParseSignatureElement(pcSignature, pMetaDataImport2);
    }
    else if (elementType == ELEMENT_TYPE_PTR) {
        m_isPtr = true;
        ParseSignatureElement(pcSignature, pMetaDataImport2);
    }
    else if (elementType == ELEMENT_TYPE_SZARRAY) {
        m_isArray = true;
        ParseSignatureElement(pcSignature, pMetaDataImport2);
    }
    else if (elementType == ELEMENT_TYPE_ARRAY) {
        m_isArray = true;
        ParseSignatureElement(pcSignature, pMetaDataImport2);
    }
    else {
        m_elementType = elementType;
        //wprintf(L"%x (%s) ", elementType, ElementTypeToString(elementType));
    }
}

LPWSTR ClrProfiler::CParameterInfo::GetTypeName(PCCOR_SIGNATURE& pcSignature, ATL::CComPtr<IMetaDataImport2> pMetaDataImport2)
{
    HRESULT hr;
    ULONG cchClassName;
    mdToken token = CorSigUncompressToken(pcSignature);

    WCHAR classNameBuffer[NAME_BUFFER_SIZE];
    if (TypeFromToken(token) == mdtTypeRef) {
        hr = pMetaDataImport2->GetTypeRefProps(token, NULL, classNameBuffer, NAME_BUFFER_SIZE, &cchClassName);
    }
    else {
        hr = pMetaDataImport2->GetTypeDefProps(token, classNameBuffer, NAME_BUFFER_SIZE, &cchClassName, NULL, NULL);
    }

    WCHAR *className = new WCHAR[cchClassName];

    StringCchCopyW(className, cchClassName, classNameBuffer);

    return className;
}

LPWSTR ClrProfiler::CParameterInfo::ElementTypeToString(CorElementType elementType)
{
    switch (elementType) {
    case ELEMENT_TYPE_END:
        return L"ELEMENT_TYPE_END";
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
    case ELEMENT_TYPE_I:				// native integer size
        return L"native int";
    case ELEMENT_TYPE_U:				// native unsigned integer size
        return L"native uint";

        // every type above PTR will be simple type
    case ELEMENT_TYPE_PTR:				// PTR <type>
        return L"ELEMENT_TYPE_PTR";
    case ELEMENT_TYPE_BYREF:			// BYREF <type>
        return L"ELEMENT_TYPE_BYREF";

        // Please use ELEMENT_TYPE_VALUETYPE. ELEMENT_TYPE_VALUECLASS is deprecated.
    case ELEMENT_TYPE_VALUETYPE:		// VALUETYPE <class Token>
        return L"ELEMENT_TYPE_VALUETYPE";
    case ELEMENT_TYPE_CLASS:			// CLASS <class Token>
        return L"ELEMENT_TYPE_CLASS";
    case ELEMENT_TYPE_VAR:				// a class type variable VAR <number>
        return L"ELEMENT_TYPE_VAR";
    case ELEMENT_TYPE_ARRAY:			// MDARRAY <type> <rank> <bcount> <bound1> ... <lbcount> <lb1> ...
        return L"ELEMENT_TYPE_ARRAY";
    case ELEMENT_TYPE_GENERICINST:		// GENERICINST <generic type> <argCnt> <arg1> ... <argn>
        return L"ELEMENT_TYPE_GENERICINST";
    case ELEMENT_TYPE_TYPEDBYREF:		// TYPEDREF  (it takes no args) a typed referece to some other type
        return L"ELEMENT_TYPE_TYPEDBYREF";

    case ELEMENT_TYPE_FNPTR:			// FNPTR <complete sig for the function including calling convention>
        return L"ELEMENT_TYPE_FNPTR";
    case ELEMENT_TYPE_OBJECT:			// Shortcut for System.Object
        return L"object";
    case ELEMENT_TYPE_SZARRAY:			// Shortcut for single dimension zero lower bound array
        return L"ELEMENT_TYPE_SZARRAY";	//SZARRAY <type>
    case ELEMENT_TYPE_MVAR:				// a method type variable MVAR <number>
        return L"ELEMENT_TYPE_MVAR";

        // This is only for binding
    case ELEMENT_TYPE_CMOD_REQD:		// required C modifier : E_T_CMOD_REQD <mdTypeRef/mdTypeDef>
        return L"ELEMENT_TYPE_CMOD_REQD";
    case ELEMENT_TYPE_CMOD_OPT:			// optional C modifier : E_T_CMOD_OPT <mdTypeRef/mdTypeDef>
        return L"ELEMENT_TYPE_CMOD_OPT";

        // This is for signatures generated internally (which will not be persisted in any way).
    case ELEMENT_TYPE_INTERNAL:			// INTERNAL <typehandle>
        return L"ELEMENT_TYPE_INTERNAL";

        // Note that this is the max of base type excluding modifiers
    case ELEMENT_TYPE_MAX:				// first invalid element type
        return L"ELEMENT_TYPE_MAX";
    default:
        return L"";
    }
}

namespace ClrProfiler {
    std::wostream& operator<<(std::wostream& out, CParameterInfo const& parameterInfo)
    {
        if (parameterInfo.m_isByref) {
            out << L"byref ";
        }

        if (parameterInfo.m_isPtr) {
            out << L"ptr ";
        }

        if (parameterInfo.m_isArray) {
            if (parameterInfo.m_isClass) {
                out << parameterInfo.m_className;
            }
            else {
                out << CParameterInfo::ElementTypeToString(parameterInfo.m_elementType);
            }

            out << "[]";
        }
        else if (parameterInfo.m_isClass) {
            out << parameterInfo.m_className;
        }
        else {
            out << CParameterInfo::ElementTypeToString(parameterInfo.m_elementType);
        }

        return out;
    }
}