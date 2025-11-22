#pragma once
#include <map>
#include "message/i_http_headers.h"

namespace message
{
	class MESSAGE HTTPHeaders : public IHTTPHeaders
	{
	public:
		// Inherited via IHTTPHeaders
		const THeaderKey GetHeaderValue(const THeaderKey& headerName) const final;
		void SetHeaderValue(const THeaderKey& headerName, const THeaderValue& headerValue) final;
		bool HasHeader(const THeaderKey& headerName) const final;
		const std::vector<THeaderKey> GetHeaderKeys() const final;

	private:
		std::map<THeaderKey, THeaderValue> m_headers;
	};
}
