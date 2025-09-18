#pragma once
#include <string>
#include <vector>

namespace parser
{
    class StringSplitter
    {
    public:
        struct Result
        {
            std::string m_startLine{ "" };
            std::vector<std::string> m_headers;
            std::string m_body;
        };

    public:
        StringSplitter(const std::string& request);
        Result GetResult();

    private:
        std::string getNextRow();

    private:
        std::string m_request;
        size_t m_ptr{ 0 };
    };
}
