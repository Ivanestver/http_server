#include "message/request_start_line.h"

namespace message
{
    Buffer& message::HttpRequestStartLine::Serialize(Buffer& buf) const
    {
        return buf;
    }

    Buffer& message::HttpRequestStartLine::Deserialize(Buffer& buf)
    {
        return buf;
    }

    std::any message::HttpRequestStartLine::GetProperty(IHTTPStartLine::Property property) const
    {
        switch (property)
        {
        case IHTTPStartLine::Property::Method:
            return std::make_any<String>(m_method);
        case IHTTPStartLine::Property::Target:
            return std::make_any<String>(m_path);
        case IHTTPStartLine::Property::Protocol:
            return std::make_any<String>(m_protocol);
        default:
            return std::any{};
        }
    }

    void message::HttpRequestStartLine::SetProperty(IHTTPStartLine::Property property, const std::any& propertyValue)
    {
        if (!propertyValue.has_value())
            return;

        switch (property)
        {
        case IHTTPStartLine::Property::Method:
            if (propertyValue.type() == typeid(String))
                m_protocol = std::any_cast<String>(propertyValue);
            break;
        case IHTTPStartLine::Property::Target:
            if (propertyValue.type() == typeid(String))
                m_protocol = std::any_cast<String>(propertyValue);
            break;
        case IHTTPStartLine::Property::Protocol:
        {
            if (propertyValue.type() == typeid(String))
                m_protocol = std::any_cast<String>(propertyValue);
            break;
        }
        default:
            return;
        }
    }
}
