//////////////////////////////////////////////////////////////////////////
#define CPF_PLUGIN_STATIC
#include "CPF/Plugin.hpp"
#include "CPF/Application.hpp"
#include "CPF/Plugin/tClassFactory.hpp"

using namespace CPF;

class BasicWindowedApp : public GOM::tUnknown<iApplication>
{
public:
	BasicWindowedApp(Plugin::iRegistry* registry, iUnknown*)
		: mpRegistry(registry)
	{}

	int32_t Run() override
	{
		return 0;
	}

	Plugin::iRegistry* GetRegistry() { return mpRegistry; }

private:
	IntrusivePtr<Plugin::iRegistry> mpRegistry;
};

CPF_APPLICATION(BasicWindowedApp);
