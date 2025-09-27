#pragma once
#include "message/i_http_request.h"

namespace parser
{
	class RequestParser
	{
	public:
		RequestParser(const String& request);

		const message::IHTTPRequest* Parse();

	private:
		String m_request;
	};
}
