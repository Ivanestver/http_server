#pragma once
#include "net_core/platform.h"
#include "core/str.h"
#include "message/i_http_request.h"
#include "server/server_defs.h"
#include <functional>
#include <unordered_map>
#include "net_core/socket.h"

namespace server
{
	class Server
	{
	public:
		void AddHandler(const String& path, Handler&& handler);
		void Run(port_t port);

	private:
		void respond(net_core::Socket&& clientSocketRef) noexcept;

	private:
		std::unordered_map<String, Handler> m_handlers;
	};
}