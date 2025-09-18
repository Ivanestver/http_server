#include "message/http_headers.h"

namespace message
{
    const std::any HTTPHeaders::GetHeaderValue(const std::string& headerName) const
    {
        const auto it = m_headers.find(headerName);
        if (it != m_headers.end())
            return it->second;
        return std::any{};
    }

    void HTTPHeaders::SetHeaderValue(const std::string& headerName, const std::any& headerValue)
    {
        m_headers[headerName] = headerValue;
    }

    bool HTTPHeaders::HasHeader(const std::string& headerName) const
    {
        return m_headers.find(headerName) != m_headers.end();
    }
}
