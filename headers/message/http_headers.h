#pragma once
#include <unordered_map>
#include "message/i_http_headers.h"

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable: 4251)
#endif

namespace message
{
	class MESSAGE HTTPHeaders : public IHTTPHeaders
	{
	public:
		// Inherited via IHTTPHeaders
		const THeaderKey GetHeaderValue(const THeaderKey& headerName) const noexcept final;
		void SetHeaderValue(const THeaderKey& headerName, const THeaderValue& headerValue) noexcept final;
		bool HasHeader(const THeaderKey& headerName) const noexcept final;
		const std::vector<THeaderKey> GetHeaderKeys() const noexcept final;

	private:
		std::unordered_map<THeaderKey, THeaderValue> m_headers;
	};
}

#ifdef _MSC_VER
#pragma warning(pop)
#endif
