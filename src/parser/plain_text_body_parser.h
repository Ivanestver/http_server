#pragma once
#include "request_body_parser.h"

namespace parser
{
	class PlainTextBodyParser : public RequestBodyParser
	{
	public:
		template<typename T>
		PlainTextBodyParser(T&& content, const String& mimeType)
			: RequestBodyParser(std::move(content), mimeType)
		{ }

		message::IHTTPBody* Parse() noexcept override;
	};

	class PlainTextBodyParserFactory : public RequestBodyParserFactory
	{
	public:
		// ”наследовано через RequestBodyParserFactory
		PRequestBodyParser Create(const String& content, const String& mimeType) const override;
	};
}