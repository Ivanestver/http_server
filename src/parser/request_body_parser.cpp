#include "request_body_parser.h"

namespace parser
{
	template<typename STR>
	inline PRequestBodyParser createParser(STR&& content, const String& mimeType)
	{
		return nullptr;
	}

	PRequestBodyParser CreateParser(const String& content, const String& mimeType)
	{
		return createParser(content, mimeType);
	}

	PRequestBodyParser CreateParser(String&& content, const String& mimeType)
	{
		return createParser(std::move(content), mimeType);
	}
}
