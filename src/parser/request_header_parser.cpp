#include <cctype>
#include "request_header_parser.h"
#include "message/http_headers.h"

using namespace message;

namespace parser
{
    IHTTPHeaders* RequestHeadersParser::Parse()
    {
        auto* headers = new HTTPHeaders();
        for (const String& line : m_request)
        {
            reset(line);
            const String headerName = getNextToken();
            skip_forbidden();
            String value = getNextToken();
            while (true)
            {
                skip_forbidden();
                String v = getNextToken();
                if (!v.is_empty())
                    value = value + v;
                else
                    break;
            }

            headers->SetHeaderValue(makeName(headerName), value);
        }
        return headers;
    }

    const String RequestHeadersParser::getNextToken()
    {
        String s;
        for (; has() && current_is_permitted(); moveNext())
        {
            s = s + current();
        }
        return s;
    }

    String RequestHeadersParser::makeName(const String& dirtyName) const
    {
        if (dirtyName.length() > 1)
            return dirtyName.substr(0, dirtyName.length() - 1);
        else
            return {};
    }
}
