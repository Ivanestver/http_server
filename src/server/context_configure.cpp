#include "context_configure.h"

namespace server
{
	std::shared_ptr<Context> context = nullptr;

	void ConfigureContext(const String& pathToRoot)
	{
		ContextSettings settings;
		settings.m_pathToRoot = pathToRoot;
		settings.m_resourcePath = settings.m_pathToRoot + String{ "resources/" };
		context.reset(new Context{ settings });
	}

	std::shared_ptr<Context> GetInnerContext()
	{
		return context;
	}
}
