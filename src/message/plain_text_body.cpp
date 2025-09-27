#include "message/plain_text_body.h"
#include <sstream>

namespace message
{
    RequestPlainTextBody::RequestPlainTextBody(const String& content, const String& mimeType)
        : HTTPBody(mimeType)
        , m_content{ content }
    {
    }

    std::vector<uint8_t> message::RequestPlainTextBody::ToBytes() const
    {
        std::vector<uint8_t> byteArray(GetSize() + 1);
        std::memcpy(byteArray.data(), m_content.data(), GetSize());
        byteArray[byteArray.size() - 1] = '\0';
        return byteArray;
    }

    String message::RequestPlainTextBody::ToString() const
    {
        return m_content;
    }

    std::unique_ptr<std::istream> message::RequestPlainTextBody::ToStream() const
    {
        return std::make_unique<std::istringstream>(m_content.data());
    }

    size_t message::RequestPlainTextBody::GetSize() const
    {
        return m_content.length();
    }

    bool message::RequestPlainTextBody::IsEmpty() const
    {
        return m_content.is_empty();
    }
}
