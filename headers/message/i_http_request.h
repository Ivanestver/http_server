#pragma once
#include "i_http_request_start_line.h"
#include "i_http_headers.h"
#include "i_http_body.h"

namespace message
{
	class IHTTPRequest
	{
	public:
		virtual ~IHTTPRequest() = default;

		virtual const IHTTPRequestStartLine* GetStartLine() const = 0;
		virtual const IHTTPHeaders* GetHeaders() const = 0;
		virtual const IHTTPBody* GetBody() const = 0;
	};
}
