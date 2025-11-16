#include "message/http_response.h"
#include <string>
#include "core/buffer.h"

namespace message
{
    void HTTPResponse::SetStatusCode(StatusCode statusCode)
    {
        m_statusCode = statusCode;
    }

    void HTTPResponse::SetHeader(const THeaderKey& key, const THeaderValue& value)
    {
        m_headers.SetHeaderValue(key, value);
    }

    ResponseWriter HTTPResponse::GetBodyWriter()
    {
        return ResponseWriter{ &m_body };
    }

	std::vector<uint8_t> HTTPResponse::toBytes()
    {
        Buffer response;
        auto writer = ResponseWriter{ &response }
            .WriteLine("HTTP/1.1 ", std::to_string((int)m_statusCode), " ", StatusCodeAsStr(m_statusCode));

        const std::vector<THeaderKey> headerKeys = m_headers.GetHeaderKeys();
        for (const THeaderKey& key : headerKeys)
            writer.WriteLine(key, ": ", m_headers.GetHeaderValue(key));

        writer.WriteLine();

        std::vector<uint8_t> result = response.to_bytes();
		std::vector<uint8_t> body = m_body.to_bytes();

        std::copy(body.begin(), body.end(), std::back_inserter(result));
        return result;
    }
}
