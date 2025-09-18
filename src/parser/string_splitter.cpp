#include "string_splitter.h"

namespace parser
{
    StringSplitter::StringSplitter(const std::string& request)
        : m_request{ request }
    {
    }

    StringSplitter::Result StringSplitter::GetResult()
    {
        Result res;
        res.m_startLine = getNextRow();
        std::string row = getNextRow();
        while (row.size() > 0)
        {
            res.m_headers.emplace_back(std::move(row));
            row = getNextRow();
        }
        res.m_body = m_request.substr(m_ptr, m_request.size());
        return res;
    }

    std::string StringSplitter::getNextRow()
    {
        std::string s;
        for (; m_ptr < m_request.size(); ++m_ptr)
        {
            if (m_request[m_ptr] == '\r' && (m_ptr + 1 != m_request.size() && m_request[m_ptr + 1] == '\n'))
            {
                m_ptr += 2;
                break;
            }
            else
                s += m_request[m_ptr];
        }
        return s;
    }
}
