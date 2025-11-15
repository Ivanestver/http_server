#pragma once
#include "core/str.h"
#include "enum_status_code.h"

namespace message
{
	class IHTTTPResponseStartLine
	{
	public:
		virtual String GetProtocol() const = 0;
		virtual StatusCode GetStatusCode() const = 0;
		virtual String GetReasonPhrase() const = 0;
	};
}