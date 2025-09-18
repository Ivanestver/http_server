#include <cctype>
#include "request_header_parser.h"
#include "message/http_headers.h"

using namespace message;

namespace parser
{
    IHTTPHeaders* RequestHeadersParser::Parse()
    {
        auto* headers = new HTTPHeaders();
        for (const std::string& line : m_request)
        {
            reset(line);
            const std::string headerName = getNextToken();
            skip_forbidden();
            std::string value = getNextToken();
            while (true)
            {
                skip_forbidden();
                std::string v = getNextToken();
                if (!v.empty())
                    value += v;
                else
                    break;
            }

            headers->SetHeaderValue(makeName(headerName), turnIntoAny(value));
        }
        return headers;
    }

    const std::string RequestHeadersParser::getNextToken()
    {
        std::string s;
        for (; has() && current_is_permitted(); moveNext())
        {
            s += current();
        }
        return s;
    }

    std::string RequestHeadersParser::makeName(const std::string& dirtyName) const
    {
        if (dirtyName.size() > 1)
            return dirtyName.substr(0, dirtyName.size() - 1);
        else
            return {};
    }

    std::any RequestHeadersParser::turnIntoAny(std::string s)
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
        // ������ ��������� ��������� ������
        if (charsCount > 0) // ���� ������� �������, �� ��� ������
            return std::any{ std::move(s) };
        else if (numbersCount > 0) // ���� ������� ������ �����
        {
            if (dotsCount == 0) // ���� ��� �����, �� �����
                return std::any{ std::stoi(s) };
            else if (dotsCount == 1) // ���� ���� �����, �� ������������
                return std::any{ std::stod(s) };
            else // ����� ����������� ���
                return std::any{};
        }
        else // �� ������, �� �����. �.�. ���������� ���
            return std::any{};
    }
}
