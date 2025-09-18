#include "message/http_request.h"

namespace message
{
	HTTPRequest::HTTPRequest(const IHTTPRequestStartLine* pStartLine, const IHTTPHeaders* pHeaders, const IHTTPBody* pBody)
		: m_pStartLine{ pStartLine }
		, m_pHeaders{ pHeaders }
		, m_pBody{ pBody }
	{
	}

	HTTPRequest::~HTTPRequest()
	{
		delete m_pStartLine;
		delete m_pHeaders;
	}

	const IHTTPRequestStartLine* HTTPRequest::GetStartLine() const
	{
		return m_pStartLine;
	}

	const IHTTPHeaders* HTTPRequest::GetHeaders() const
	{
		return m_pHeaders;
	}

	const IHTTPBody* HTTPRequest::GetBody() const
	{
		return m_pBody;
	}
}
