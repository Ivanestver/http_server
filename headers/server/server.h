#pragma once
#include "net_core/platform.h"
#include "core/str.h"
#include "message/i_http_request.h"
#include "message/http_response.h"
#include <functional>
#include <unordered_map>
#include "server/export_decl.h"

namespace server
{
	class SERVER Server
	{
	public:
		using Handler = std::function<void(const message::IHTTPRequest*, message::HTTPResponse&)>;

	public:
		void AddHandler(const String& path, Handler&& handler);
		void Run(port_t port);

	private:
		std::unordered_map<String, Handler> m_handlers;
	};
}