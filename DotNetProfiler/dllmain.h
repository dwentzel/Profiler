// dllmain.h : Declaration of module class.

class CDotNetProfilerModule : public ATL::CAtlDllModuleT< CDotNetProfilerModule >
{
public :
	DECLARE_LIBID(LIBID_DotNetProfilerLib)
	DECLARE_REGISTRY_APPID_RESOURCEID(IDR_DOTNETPROFILER, "{476dd983-1236-44c4-83b4-f4752bd4ce01}")
};

extern class CDotNetProfilerModule _AtlModule;
