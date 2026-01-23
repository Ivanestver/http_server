#include "plain_text_body_parser.h"
#include "message/plain_text_body.h"

namespace parser
{
	message::IHTTPBody* PlainTextBodyParser::Parse() noexcept
	{
		String content = get_raw();
		return new message::RequestPlainTextBody{ content, GetMimeType() };
	}

	PRequestBodyParser PlainTextBodyParserFactory::Create(const String& content, const String& mimeType) const
	{
		return std::make_unique<PlainTextBodyParser>(content, mimeType);
	}
}
