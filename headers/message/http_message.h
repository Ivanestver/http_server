#pragma once
#include "core/iserializable.h"
#include "i_http_start_line.h"
#include "i_http_headers.h"

namespace message
{
	class HTTPMessage : public ISerializable, IDeserializable
	{
	public:
		virtual ~HTTPMessage() = default;

		virtual const IHTTPStartLine* GetStartLine() const = 0;
		virtual IHTTPStartLine* GetStartLine() = 0;

		virtual const IHTTPHeaders* GetHeaders() const = 0;
		virtual IHTTPHeaders* GetHeaders() = 0;

		// Унаследовано через ISerializable
		Buffer& Serialize(Buffer& buf) const override;
		// Унаследовано через IDeserializable
		Buffer& Deserialize(Buffer& buf) override;
	};
}