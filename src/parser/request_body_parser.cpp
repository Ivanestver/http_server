#include "request_body_parser.h"
#include <map>
#include "plain_text_body_parser.h"
#include "body_factories_storage.h"

namespace parser
{
	const String& RequestBodyParser::GetMimeType() const
	{
		return m_mimeType;
	}

	template<typename STR>
	inline PRequestBodyParser createParser(STR&& content, const String& mimeType)
	{
		BodyFactoriesStorage& instance = BodyFactoriesStorage::GetStorage();
		auto* factory = instance.GetFactory(mimeType);
		if (factory)
			return factory->Create(std::forward<STR>(content), mimeType);
		else
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
