#pragma once
#include "core/str.h"

namespace message
{
	using THeaderName = String;
	using THeaderValue = String;

    class IHTTPHeaders
    {
    public:
        virtual ~IHTTPHeaders() = default;

        virtual const THeaderValue GetHeaderValue(const THeaderName& headerName) const = 0;
        virtual void SetHeaderValue(const THeaderName& headerName, const THeaderValue& headerValue) = 0;
        virtual bool HasHeader(const THeaderName& headerName) const = 0;
    };
}
