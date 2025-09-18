#pragma once
#include <string>

namespace message
{
	class IHTTPRequestStartLine
	{
	public:
		virtual const std::string GetMethod() const = 0;
		virtual const std::string GetPath() const = 0;
		virtual const std::string GetProtocol() const = 0;
	};
}
