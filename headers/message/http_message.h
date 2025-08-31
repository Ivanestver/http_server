#pragma once
#include "core/iserializable.h"
#include "i_http_start_line.h"
#include "i_http_headers.h"

namespace message
{
	class IHTTPMessage : public ISerializable, IDeserializable
	{
	public:
		virtual ~IHTTPMessage() = default;

		virtual const IHTTPStartLine* GetStartLine() const = 0;
		virtual const IHTTPHeaders* GetHeaders() const = 0;
	};
}