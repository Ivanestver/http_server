#pragma once
#include "message/i_http_request.h"
#include "parser/export_decl.h"

namespace parser
{
	class PARSER RequestParser
	{
	public:
		RequestParser(const String& request);

		const message::IHTTPRequest* Parse() noexcept;

	private:
		String m_request;
	};
}
