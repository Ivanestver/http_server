#pragma once
#include "message/i_http_request_start_line.h"

namespace message
{
	class HTTPRequestStartLine : public IHTTPRequestStartLine
	{
	public:
		HTTPRequestStartLine(const String& method, const String& path, const String& protocol);

		// Inherited via IHTTPRequestStartLine
		const String GetMethod() const override;
		const String GetPath() const override;
		const String GetProtocol() const override;

	private:
		String m_method;
		String m_path;
		String m_protocol;
	};
}