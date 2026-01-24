#include "string_splitter.h"

namespace parser
{
    StringSplitter::StringSplitter(const String& request)
        : m_request{ request }
    {
    }

    StringSplitter::Result StringSplitter::GetResult() noexcept
    {
        Result res;
        res.m_startLine = getNextRow();
        String row = getNextRow();
        while (!row.is_empty() && rowIsHeader(row))
        {
            res.m_headers.emplace_back(std::move(row));
            row = getNextRow();
        }
        res.m_body = m_request.substr(m_ptr, m_request.length());
        return res;
    }

    String StringSplitter::getNextRow() noexcept
    {
        String s;
        for (; m_ptr < m_request.length(); ++m_ptr)
        {
            if (m_request[m_ptr] == '\r' && (m_ptr + 1 != m_request.length() && m_request[m_ptr + 1] == '\n'))
            {
                m_ptr += 2;
                break;
            }
            else
                s = s + m_request[m_ptr];
        }
        return s;
    }

    bool StringSplitter::rowIsHeader(const String& row) const noexcept
    {
        return !row.contains(':');
    }
}
