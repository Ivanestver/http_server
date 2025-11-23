#include "server/context.h"
#include "context_configure.h"

namespace server
{
	Context::Context(const String& pathToRoot)
		: m_pathToRoot{ pathToRoot }
	{
	}

	const String& Context::GetPathToRoot() const
	{
		return m_pathToRoot;
	}

	Context* GetContext()
	{
		return GetInnerContext();
	}
}
