#pragma once
#include "server/export_decl.h"
#include "core/str.h"
#include "file_dispatcher.h"
#include <memory>

namespace server
{
	struct ContextSettings
	{
		String m_pathToRoot;
		String m_resourcePath;
	};

	class SERVER Context
	{
	public:
		Context(const ContextSettings& settings);

		const String& GetPathToRoot() const;
		const String& GetResourcePath() const;

		std::unique_ptr<FileDispatcher> MakeFileDispatcher(const String& pathToFile) const;

	private:
		ContextSettings m_settings;
	};

	SERVER Context* GetContext();
}