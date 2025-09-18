#pragma once
#include "request_part_parser.h"
#include "message/i_http_headers.h"
#include <vector>

namespace parser
{
    class RequestHeadersParser : public RequestPartParser<message::IHTTPHeaders>
    {
    public:
        template<typename T>
        RequestHeadersParser(T&& request)
            : RequestPartParser(std::string{})
        {
            m_request = std::move(request);
        }

        message::IHTTPHeaders* Parse() override;

    private:
        const std::string getNextToken();
        std::string makeName(const std::string& dirtyName) const;
        std::any turnIntoAny(std::string s);

    private:
        std::vector<std::string> m_request;
    };
}
