#pragma once
#include "message/i_http_request_start_line.h"

namespace message
{
	class HTTPRequestStartLine : public IHTTPRequestStartLine
	{
	public:
		HTTPRequestStartLine(const std::string& method, const std::string& path, const std::string& protocol);

		// Inherited via IHTTPRequestStartLine
		const std::string GetMethod() const override;
		const std::string GetPath() const override;
		const std::string GetProtocol() const override;

	private:
		std::string m_method;
		std::string m_path;
		std::string m_protocol;
	};
}