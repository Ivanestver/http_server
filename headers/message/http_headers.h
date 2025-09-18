#pragma once
#include <map>
#include "message/i_http_headers.h"

namespace message
{
	class HTTPHeaders : public IHTTPHeaders
	{
	public:
		// Inherited via IHTTPHeaders
		const std::any GetHeaderValue(const std::string& headerName) const final;
		void SetHeaderValue(const std::string& headerName, const std::any& headerValue) final;
		bool HasHeader(const std::string& headerName) const final;

	private:
		std::map<std::string, std::any> m_headers;
	};
}
