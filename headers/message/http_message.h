#pragma once
#include <string>
#include <any>

namespace message
{
	class IHTTPStartLine
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

	class IHTTPHeaders
	{
	public:
		virtual ~IHTTPHeaders() = default;

		virtual const std::string GetHeader(const std::string& header) const = 0;
	};

	class IHTTPMessage
	{
	public:
		virtual ~IHTTPMessage() = default;

		virtual const IHTTPStartLine* GetStartLine() const = 0;
		virtual const IHTTPHeaders* GetHeaders() const = 0;
	};
}