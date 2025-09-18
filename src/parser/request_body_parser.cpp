#include "request_body_parser.h"

namespace parser
{
	template<typename STR>
	inline PRequestBodyParser createParser(STR&& content, const std::string& mimeType)
	{
		return nullptr;
	}

	PRequestBodyParser CreateParser(const std::string& content, const std::string& mimeType)
	{
		return createParser(content, mimeType);
	}

	PRequestBodyParser CreateParser(std::string&& content, const std::string& mimeType)
	{
		return createParser(std::move(content), mimeType);
	}
}
