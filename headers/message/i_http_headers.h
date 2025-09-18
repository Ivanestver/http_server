#pragma once
#include <string>
#include <any>

namespace message
{
    class IHTTPHeaders
    {
    public:
        virtual ~IHTTPHeaders() = default;

        virtual const std::any GetHeaderValue(const std::string& headerName) const = 0;
        virtual void SetHeaderValue(const std::string& headerName, const std::any& headerValue) = 0;
        virtual bool HasHeader(const std::string& headerName) const = 0;

        // helper function
        template<typename T>
        T GetHeaderValueAs(const std::string& headerName) const
        {
            return std::any_cast<T>(GetHeaderValue(headerName));
        }
    };
}
