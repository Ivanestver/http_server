#include "parser/request_parser.h"
#include "string_splitter.h"
#include "request_start_line_parser.h"
#include "request_header_parser.h"
#include "request_body_parser.h"
#include "message/http_request.h"

using namespace message;

namespace parser
{
    RequestParser::RequestParser(const std::string& request)
        : m_request{ request }
    {
    }

    const IHTTPRequest* RequestParser::Parse()
    {
        StringSplitter::Result result = StringSplitter{ m_request }.GetResult();

        RequestStartLineParser startLineParser(std::move(result.m_startLine));
        auto startLine = std::unique_ptr<IHTTPRequestStartLine>{ startLineParser.Parse() };
        if (!startLine)
            return nullptr;

        RequestHeadersParser headersParser{ std::move(result.m_headers) };
        auto headers = std::unique_ptr<IHTTPHeaders>{ headersParser.Parse() };
        const std::string contentType = "Content-Type";
        if (!headers || !headers->HasHeader(contentType))
            return nullptr;

        const std::string mimeType = headers->GetHeaderValueAs<std::string>(contentType);

        PRequestBodyParser bodyParser = CreateParser(std::move(result.m_body), mimeType);
        auto body = std::unique_ptr<IHTTPBody>{ bodyParser->Parse() };
        if (!body)
            return nullptr;

        return new HTTPRequest{ startLine.release(), headers.release(), body.release() };
    }
}
