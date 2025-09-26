#include "message/http_headers.h"

namespace message
{
    const std::any HTTPHeaders::GetHeaderValue(const String& headerName) const
    {
        const auto it = m_headers.find(headerName);
        if (it != m_headers.end())
            return it->second;
        return std::any{};
    }

    void HTTPHeaders::SetHeaderValue(const String& headerName, const std::any& headerValue)
    {
        m_headers[headerName] = headerValue;
    }

    bool HTTPHeaders::HasHeader(const String& headerName) const
    {
        return m_headers.find(headerName) != m_headers.end();
    }
}
