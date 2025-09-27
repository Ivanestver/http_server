#pragma once
#include "request_part_parser.h"
#include "message/i_http_headers.h"
#include <vector>

namespace parser
{
    class RequestHeadersParser : public RequestPartParser<message::IHTTPHeaders>
    {
    public:
        RequestHeadersParser(std::vector<String>&& request)
            : RequestPartParser(String{})
        {
            m_request = std::move(request);
        }

        message::IHTTPHeaders* Parse() override;

    private:
        const String getNextToken();
        String makeName(const String& dirtyName) const;
        std::any turnIntoAny(String s);

    private:
        std::vector<String> m_request;
    };
}
