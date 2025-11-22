#pragma once
#include "core/str.h"
#include <vector>
#include "message/export_decl.h"

namespace message
{
	using THeaderKey = String;
	using THeaderValue = String;

    class MESSAGE IHTTPHeaders
    {
    public:
        virtual ~IHTTPHeaders() = default;

        virtual const THeaderValue GetHeaderValue(const THeaderKey& headerName) const = 0;
        virtual void SetHeaderValue(const THeaderKey& headerName, const THeaderValue& headerValue) = 0;
        virtual bool HasHeader(const THeaderKey& headerName) const = 0;
        virtual const std::vector<THeaderKey> GetHeaderKeys() const = 0;
    };
}
