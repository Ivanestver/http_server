#pragma once
#include "core/str.h"
#include "enum_status_code.h"
#include "core/optional.h"

namespace message
{
	class IHTTPResponseStartLine
	{
	public:
		virtual ~IHTTPResponseStartLine() = default;

		virtual String GetProtocol() const = 0;
		virtual StatusCode GetStatusCode() const = 0;
		virtual std::optional<String> GetReasonPhrase() const = 0;
	};
}