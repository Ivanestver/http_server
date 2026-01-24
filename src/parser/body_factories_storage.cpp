#include "body_factories_storage.h"
#include "plain_text_body_parser.h"

namespace parser
{
    BodyFactoriesStorage& BodyFactoriesStorage::GetStorage()
    {
        static BodyFactoriesStorage instance;
        return instance;
    }

    std::shared_ptr<RequestBodyParserFactory> BodyFactoriesStorage::GetFactory(const String& mimeType) const
    {
        const auto it = m_factories.find(mimeType);
        if (it != m_factories.end())
            return it->second;
        else
            return nullptr;
    }

    BodyFactoriesStorage::BodyFactoriesStorage()
    {
        Register<PlainTextBodyParserFactory>("text/plain");
    }
}
