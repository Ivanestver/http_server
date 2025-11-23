#include "context_configure.h"
#include <memory>

namespace server
{
	std::unique_ptr<Context> context = nullptr;

	void ConfigureContext()
	{
		ContextSettings settings;
		settings.m_pathToRoot = "./";
		settings.m_resourcePath = "./resources";
		context.reset(new Context{ settings });
	}

	Context* GetInnerContext()
	{
		return context.get();
	}
}
