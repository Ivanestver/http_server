#pragma once
#include <map>
#include "message/i_http_headers.h"

namespace message
{
	class HTTPHeaders : public IHTTPHeaders
	{
	public:
		// Inherited via IHTTPHeaders
		const std::any GetHeaderValue(const String& headerName) const final;
		void SetHeaderValue(const String& headerName, const std::any& headerValue) final;
		bool HasHeader(const String& headerName) const final;

	private:
		std::map<String, std::any> m_headers;
	};
}
