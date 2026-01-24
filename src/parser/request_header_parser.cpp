#include <cctype>
#include "request_header_parser.h"
#include "message/http_headers.h"
#include <memory>

using namespace message;

namespace parser
{
    RequestHeadersParser::RequestHeadersParser(std::vector<String>&& request) noexcept
		: RequestPartParser(String{})
	{
		m_request = std::move(request);
	}

    IHTTPHeaders* RequestHeadersParser::Parse() noexcept
    {
        auto headers = std::make_unique<HTTPHeaders>();
        for (const String& line : m_request)
        {
            reset(line);
            const String headerName = getNextToken();
            skip_forbidden();
            String value = getNextToken();
            size_t length = value.length();
            while (length < line.length())
            {
                skip_forbidden();
                String v = getNextToken();
                if (!v.is_empty())
                {
                    value = value + v;
                    length = value.length();
                }
                else
                    break;
            }

            headers->SetHeaderValue(makeName(headerName), value);
        }
        return headers.release();
    }

    const String RequestHeadersParser::getNextToken() noexcept
    {
        String s;
        for (; has_next() && current_is_permitted(); moveNext())
        {
            s = s + current();
        }
        return s;
    }

    String RequestHeadersParser::makeName(const String& dirtyName) const noexcept
    {
        if (dirtyName.length() > 1)
            return dirtyName.substr(0, dirtyName.length() - 1);
        else
            return {};
    }
}
