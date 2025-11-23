#pragma once
#include "server/context.h"

namespace server
{
	void ConfigureContext(const String& pathToRoot);
	Context* GetInnerContext();
}