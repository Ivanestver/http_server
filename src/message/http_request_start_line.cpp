#include "message/http_request_start_line.h"

namespace message
{
	HTTPRequestStartLine::HTTPRequestStartLine(const String& method, const String& path, const String& protocol)
		: m_method{ method }
		, m_path{ path }
		, m_protocol{ protocol }
	{
	}

	const String HTTPRequestStartLine::GetMethod() const
	{
		return m_method;
	}

	const String HTTPRequestStartLine::GetPath() const
	{
		return m_path;
	}

	const String HTTPRequestStartLine::GetProtocol() const
	{
		return m_protocol;
	}
}
