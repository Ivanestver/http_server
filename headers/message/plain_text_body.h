#pragma once
#include "message/http_body.h"

namespace message
{
	class RequestPlainTextBody : public HTTPBody
	{
	public:
		RequestPlainTextBody(const String& content, const String& mimeType);

		// ”наследовано через IHTTPBody
		std::vector<uint8_t> ToBytes() const override;
		String ToString() const override;
		std::unique_ptr<std::istream> ToStream() const override;
		size_t GetSize() const override;
		bool IsEmpty() const override;

	private:
		String m_content;
	};
}