#pragma once
#include "core/str.h"
#include <any>

namespace message
{
    class IHTTPHeaders
    {
    public:
        virtual ~IHTTPHeaders() = default;

        virtual const std::any GetHeaderValue(const String& headerName) const = 0;
        virtual void SetHeaderValue(const String& headerName, const std::any& headerValue) = 0;
        virtual bool HasHeader(const String& headerName) const = 0;

        // helper function
        template<typename T>
        T GetHeaderValueAs(const String& headerName) const
        {
            return std::any_cast<T>(GetHeaderValue(headerName));
        }
    };
}
