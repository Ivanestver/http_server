#pragma once
#include "server/export_decl.h"
#include "core/str.h"

namespace server
{
	class SERVER Context
	{
	public:
		Context(const String& pathToRoot);

		const String& GetPathToRoot() const;

	private:
		String m_pathToRoot;
	};

	SERVER Context* GetContext();
}