#pragma once
#include <map>
#include "message/i_http_headers.h"

namespace message
{
	class HTTPHeaders : public IHTTPHeaders
	{
	public:
		// Inherited via IHTTPHeaders
		const THeaderName GetHeaderValue(const THeaderName& headerName) const final;
		void SetHeaderValue(const THeaderName& headerName, const THeaderValue& headerValue) final;
		bool HasHeader(const THeaderName& headerName) const final;

	private:
		std::map<THeaderName, THeaderValue> m_headers;
	};
}
