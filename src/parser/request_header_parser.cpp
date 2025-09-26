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

            headers->SetHeaderValue(makeName(headerName), turnIntoAny(value));
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

    std::any RequestHeadersParser::turnIntoAny(String s)
    {
        size_t charsCount{ 0 };
        size_t numbersCount{ 0 };
        size_t dotsCount{ 0 };
        for (char c : s)
        {
            if (std::isdigit(c))
                numbersCount++;
            else if (c == '.')
                dotsCount++;
            else
                charsCount++;
        }
        // Теперь проверяем возможные случаи
        if (charsCount > 0) // Если имеются символы, то это строка
            return std::any{ std::move(s) };
        else if (numbersCount > 0) // Если имеются только цифры
        {
            if (dotsCount == 0) // Если нет точек, то целое
                return std::any{ ToIntegral<int>(s) };
            else if (dotsCount == 1) // Если одна точка, то вещественное
                return std::any{ ToFloating<double>(s) };
            else // Иначе неизвестный тип
                return std::any{};
        }
        else // Ни символ, ни число. Т.е. неизвестно что
            return std::any{};
    }
}
