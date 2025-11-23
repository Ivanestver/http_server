#include "context_configure.h"
#include <memory>

namespace server
{
	std::unique_ptr<Context> context = nullptr;

	void ConfigureContext(const String& pathToRoot)
	{
		ContextSettings settings;
		settings.m_pathToRoot = pathToRoot;
		settings.m_resourcePath = settings.m_pathToRoot + String{ "resources/" };
		context.reset(new Context{ settings });
	}

	Context* GetInnerContext()
	{
		return context.get();
	}
}
