#include "request_start_line_parser.h"
#include "message/http_request_start_line.h"
#include <array>
using namespace message;

namespace parser
{
    IHTTPRequestStartLine* RequestStartLineParser::Parse()
    {
        const std::string method = parseMethod();
        if (method.empty())
            return nullptr;

        const std::string path = parsePath();
        if (path.empty())
            return nullptr;

        const std::string protocol = parseProtocol();
        if (protocol.empty())
            return nullptr;
        else
            return new HTTPRequestStartLine{ method, path, protocol };
    }

    std::string RequestStartLineParser::parseMethod()
    {
        skip_forbidden();
        std::string method;
        // parse a method
        for (; has() && current_is_permitted(); moveNext())
            method += current();

        if (isValidMethod(method))
            return method;
        else
            return {};
    }

    bool RequestStartLineParser::isValidMethod(const std::string method)
    {
        static std::array<std::string, 5> m_predefinedMethods{
           "GET", "POST", "PUT", "DELETE", "PATCH"
        };
        return std::find(m_predefinedMethods.begin(), m_predefinedMethods.end(), method) != m_predefinedMethods.end();
    }

    std::string RequestStartLineParser::parsePath()
    {
        skip_forbidden();
        if (current() != '/')
            return {};

        std::string path;
        for (; has() && current_is_permitted(); moveNext())
            path += current();
        return path;
    }

    std::string RequestStartLineParser::parseProtocol()
    {
        skip_forbidden();
        std::string protocol;
        // First parse the protocol itself
        for (size_t i = 0; i < 4 && has() && current_is_permitted(); moveNext(), i++)
            protocol += current();

        if (protocol != "HTTP")
            return protocol;

        // then parse the protocol version
        for (; has() && current_is_permitted(); moveNext())
            protocol += current();

        if (isValidProtocol(protocol))
            return protocol;
        else
            return {};
    }

    bool RequestStartLineParser::isValidProtocol(const std::string& protocol)
    {
        static std::array<std::string, 4> protocols{
           "HTTP/0.9", "HTTP/1.0", "HTTP/1.1", "HTTP/2.0"
        };
        return std::find(protocols.begin(), protocols.end(), protocol) != protocols.end();
    }
}
