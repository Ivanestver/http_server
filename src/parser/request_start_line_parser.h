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

        message::IHTTPRequestStartLine* Parse() noexcept override;

    private:
        String parseMethod() noexcept;
        bool isValidMethod(const String method) noexcept;
        String parsePath() noexcept;
        String parseProtocol() noexcept;

        bool isValidProtocol(const String& protocol) noexcept;
    };

}
