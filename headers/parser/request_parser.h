#pragma once
#include "message/i_http_request.h"

namespace parser
{
	class RequestParser
	{
	public:
		RequestParser(const std::string& request);

		const message::IHTTPRequest* Parse();

	private:
		std::string m_request;
	};
}
