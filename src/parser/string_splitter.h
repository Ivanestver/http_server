#pragma once
#include <vector>
#include "core/str.h"

namespace parser
{
    class StringSplitter
    {
    public:
        struct Result
        {
            String m_startLine{ "" };
            std::vector<String> m_headers;
            String m_body;
        };

    public:
        StringSplitter(const String& request);
        Result GetResult();

    private:
        String getNextRow();

    private:
        String m_request;
        size_t m_ptr{ 0 };
    };
}
