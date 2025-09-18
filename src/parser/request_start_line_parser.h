#pragma once
#include "request_part_parser.h"
#include "message/i_http_request_start_line.h"

namespace parser
{
    class RequestStartLineParser : public RequestPartParser<message::IHTTPRequestStartLine>
    {
    public:
        template<typename STR>
        RequestStartLineParser(STR&& rawRequest)
            : RequestPartParser(std::move(rawRequest))
        {
        }

        message::IHTTPRequestStartLine* Parse() override;

    private:
        std::string parseMethod();
        bool isValidMethod(const std::string method);
        std::string parsePath();
        std::string parseProtocol();

        bool isValidProtocol(const std::string& protocol);
    };

}
