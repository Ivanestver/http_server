#include "message/http_request_start_line.h"

namespace message
{
	HTTPRequestStartLine::HTTPRequestStartLine(const std::string& method, const std::string& path, const std::string& protocol)
		: m_method{ method }
		, m_path{ path }
		, m_protocol{ protocol }
	{
	}

	const std::string HTTPRequestStartLine::GetMethod() const
	{
		return m_method;
	}

	const std::string HTTPRequestStartLine::GetPath() const
	{
		return m_path;
	}

	const std::string HTTPRequestStartLine::GetProtocol() const
	{
		return m_protocol;
	}
}
