#pragma once
#include <functional>
#include "message/i_http_request.h"
#include "message/http_response.h"

namespace server
{
	using Handler = std::function<void(const message::IHTTPRequest*, message::HTTPResponse&)>;
}