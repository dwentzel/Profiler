// dllmain.h : Declaration of module class.

class CClrProfilerModule : public ATL::CAtlDllModuleT< CClrProfilerModule >
{
public :
	DECLARE_LIBID(LIBID_ClrProfilerLib)
	DECLARE_REGISTRY_APPID_RESOURCEID(IDR_CLRPROFILER, "{34AB7580-3557-4F27-ADB1-B46019BC7F28}")
};

extern class CClrProfilerModule _AtlModule;
