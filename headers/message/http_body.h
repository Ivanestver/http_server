#pragma once
#include "message/i_http_body.h"

namespace message
{
	class HTTPBody : public IHTTPBody
	{
	public:
		explicit HTTPBody(const String& mimeType);
		String GetMIMEType() const override;

	private:
		String m_mimeType;
	};
}