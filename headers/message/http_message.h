#pragma once
#include "core/iserializable.h"
#include "i_http_start_line.h"
#include "i_http_headers.h"
#include "i_http_body.h"

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

		virtual const IHTTPBody* GetBody() const = 0;
		virtual IHTTPBody* GetBody() = 0;

		// ”наследовано через ISerializable
		Buffer& Serialize(Buffer& buf) const override;
		// ”наследовано через IDeserializable
		Buffer& Deserialize(Buffer& buf) override;
	};
}