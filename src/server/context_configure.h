#pragma once
#include "server/context.h"

namespace server
{
	void ConfigureContext();
	Context* GetInnerContext();
}