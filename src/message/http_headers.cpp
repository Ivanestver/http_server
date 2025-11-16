#include "message/http_headers.h"

namespace message
{
    const THeaderValue HTTPHeaders::GetHeaderValue(const THeaderName& headerName) const
    {
        const auto it = m_headers.find(headerName);
        if (it != m_headers.end())
            return it->second;
        return THeaderValue{};
    }

    void HTTPHeaders::SetHeaderValue(const THeaderName& headerName, const THeaderValue& headerValue)
    {
        m_headers[headerName] = headerValue;
    }

    bool HTTPHeaders::HasHeader(const THeaderName& headerName) const
    {
        return m_headers.find(headerName) != m_headers.end();
    }
}
