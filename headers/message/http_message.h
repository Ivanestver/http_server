#pragma once
#include <string>
#include <any>
#include "core/iserializable.h"

namespace message
{
	class IHTTPStartLine : public ISerializable, IDeserializable
	{
	public:
		enum class Property
		{
			Unknown,
			Method,
			Target,
			Protocol,
			StatusCode,
			StatusCodeText
		};

	public:
		virtual ~IHTTPStartLine() = default;

		virtual std::any GetProperty(IHTTPStartLine::Property property) const = 0;
		virtual void SetProperty(IHTTPStartLine::Property property, const std::any& propertyValue) = 0;
	};

	class IHTTPHeaders : public ISerializable, IDeserializable
	{
	public:
		virtual ~IHTTPHeaders() = default;

		virtual const String GetHeader(const String& header) const = 0;
	};

	class IHTTPMessage : public ISerializable, IDeserializable
	{
	public:
		virtual ~IHTTPMessage() = default;

		virtual const IHTTPStartLine* GetStartLine() const = 0;
		virtual const IHTTPHeaders* GetHeaders() const = 0;
	};
}