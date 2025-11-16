#include "message/http_headers.h"

namespace message
{
    const THeaderValue HTTPHeaders::GetHeaderValue(const THeaderKey& headerName) const
    {
        const auto it = m_headers.find(headerName);
        if (it != m_headers.end())
            return it->second;
        return THeaderValue{};
    }

    void HTTPHeaders::SetHeaderValue(const THeaderKey& headerName, const THeaderValue& headerValue)
    {
        m_headers[headerName] = headerValue;
    }

    bool HTTPHeaders::HasHeader(const THeaderKey& headerName) const
    {
        return m_headers.find(headerName) != m_headers.end();
    }

    const std::vector<THeaderKey> HTTPHeaders::GetHeaderKeys() const
    {
        std::vector<THeaderKey> keys;
        keys.reserve(m_headers.size());
        for (const auto& p : m_headers)
            keys.emplace_back(p.first);
        return keys;
    }
}
