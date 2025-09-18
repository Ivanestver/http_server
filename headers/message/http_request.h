#pragma once
#include "message/i_http_request.h"

namespace message
{
	class HTTPRequest : public IHTTPRequest
	{
	public:
		HTTPRequest(const IHTTPRequestStartLine* pStartLine, const IHTTPHeaders* pHeaders, const IHTTPBody* pBody);
		~HTTPRequest();

		// Inherited via IHTTPRequest
		const IHTTPRequestStartLine* GetStartLine() const final;
		const IHTTPHeaders* GetHeaders() const final;
		const IHTTPBody* GetBody() const final;

	private:
		const IHTTPRequestStartLine* m_pStartLine{ nullptr };
		const IHTTPHeaders* m_pHeaders{ nullptr };
		const IHTTPBody* m_pBody{ nullptr };
	};
}
