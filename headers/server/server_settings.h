#pragma once
#include "server/export_decl.h"
#include "server_defs.h"
#include "net_core/platform.h"

namespace server
{
	SERVER void AddHandler(const String& path, Handler&& handler);
	SERVER void Run(port_t port, int argc, char* argv[]);
}