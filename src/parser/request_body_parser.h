#pragma once
#include <memory>
#include "request_part_parser.h"
#include "message/i_http_body.h"

namespace parser
{
    class RequestBodyParser : public RequestPartParser<message::IHTTPBody>
    {
    public:
        template<typename T>
        RequestBodyParser(T&& content, const std::string& mimeType)
            : RequestPartParser(std::move(content))
        {
        }
        virtual ~RequestBodyParser() = default;

    private:
        std::string m_mimeType;
    };

    using PRequestBodyParser = std::unique_ptr<RequestBodyParser>;

    PRequestBodyParser CreateParser(const std::string& content, const std::string& mimeType);
    PRequestBodyParser CreateParser(std::string&& content, const std::string& mimeType);
}
