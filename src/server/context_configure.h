#pragma once
#include "server/context.h"
#include <memory>

namespace server
{
	void ConfigureContext(const String& pathToRoot);
	std::shared_ptr<Context> GetInnerContext();
}