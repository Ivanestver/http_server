#include "server/context.h"
#include "context_configure.h"

namespace server
{
	Context::Context(const ContextSettings& settings)
		: m_settings{ settings }
	{
	}

	const String& Context::GetPathToRoot() const
	{
		return m_settings.m_pathToRoot;
	}

	const String& Context::GetResourcePath() const
	{
		return m_settings.m_resourcePath;
	}

	std::unique_ptr<FileDispatcher> Context::MakeFileDispatcher(const String& pathToFile) const
	{
		return std::make_unique<FileDispatcher>(m_settings.m_resourcePath + pathToFile);
	}

	std::shared_ptr<Context> GetContext()
	{
		return GetInnerContext();
	}
}
