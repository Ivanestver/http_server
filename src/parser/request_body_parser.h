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
        RequestBodyParser(T&& content, const String& mimeType)
            : RequestPartParser(std::move(content))
            , m_mimeType{ mimeType }
        {
        }
        virtual ~RequestBodyParser() = default;

        message::IHTTPBody* Parse() override;

    private:
        String m_mimeType;
    };

    using PRequestBodyParser = std::unique_ptr<RequestBodyParser>;

    PRequestBodyParser CreateParser(const String& content, const String& mimeType);
    PRequestBodyParser CreateParser(String&& content, const String& mimeType);
}
