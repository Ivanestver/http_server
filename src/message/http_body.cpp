#include "message/http_body.h"

namespace message
{
	HTTPBody::HTTPBody(const String& mimeType)
		: m_mimeType{ mimeType }
	{
	}
	String HTTPBody::GetMIMEType() const
	{
		return m_mimeType;
	}
}
