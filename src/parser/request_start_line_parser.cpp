#include "request_start_line_parser.h"
#include "message/http_request_start_line.h"
#include <array>
using namespace message;

namespace parser
{
    IHTTPRequestStartLine* RequestStartLineParser::Parse() noexcept
    {
        const String method = parseMethod();
        if (method.is_empty())
            return nullptr;

        const String path = parsePath();
        if (path.is_empty())
            return nullptr;

        const String protocol = parseProtocol();
        if (protocol.is_empty())
            return nullptr;
        else
            return new HTTPRequestStartLine{ method, path, protocol };
    }

    String RequestStartLineParser::parseMethod() noexcept
    {
        skip_forbidden();
        String method;
        // parse a method
        for (; has() && current_is_permitted(); moveNext())
            method = method + current();

        if (isValidMethod(method))
            return method;
        else
            return {};
    }

    bool RequestStartLineParser::isValidMethod(const String method) noexcept
    {
        static std::array<String, 5> m_predefinedMethods{
           "GET", "POST", "PUT", "DELETE", "PATCH"
        };
        return std::find(m_predefinedMethods.begin(), m_predefinedMethods.end(), method) != m_predefinedMethods.end();
    }

    String RequestStartLineParser::parsePath() noexcept
    {
        skip_forbidden();
        if (current() != '/')
            return {};

        String path;
        for (; has() && current_is_permitted(); moveNext())
            path = path + current();
        return path;
    }

    String RequestStartLineParser::parseProtocol() noexcept
    {
        skip_forbidden();
        String protocol;
        // First parse the protocol itself
        for (size_t i = 0; i < 4 && has() && current_is_permitted(); moveNext(), i++)
            protocol = protocol + current();

        if (protocol != String{ "HTTP" })
            return protocol;

        // then parse the protocol version
        for (; has() && current_is_permitted(); moveNext())
            protocol = protocol + current();

        if (isValidProtocol(protocol))
            return protocol;
        else
            return {};
    }

    bool RequestStartLineParser::isValidProtocol(const String& protocol) noexcept
    {
        static std::array<String, 4> protocols{
           "HTTP/0.9", "HTTP/1.0", "HTTP/1.1", "HTTP/2.0"
        };
        return std::find(protocols.begin(), protocols.end(), protocol) != protocols.end();
    }
}
