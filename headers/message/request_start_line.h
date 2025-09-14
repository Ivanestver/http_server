#pragma once

#include "message/i_http_start_line.h"
#include <core/str.h>

namespace message
{
	class HttpRequestStartLine : public IHTTPStartLine
	{
	public:
		// Унаследовано через IHTTPStartLine
		Buffer& Serialize(Buffer& buf) const override;
		Buffer& Deserialize(Buffer& buf) override;
		std::any GetProperty(IHTTPStartLine::Property property) const override;
		void SetProperty(IHTTPStartLine::Property property, const std::any& propertyValue) override;

	private:
		String m_method;
		String m_path;
		String m_protocol;
	};
}