#pragma once
#include "core/str.h"

namespace message
{
	class IHTTPRequestStartLine
	{
	public:
		virtual const String GetMethod() const = 0;
		virtual const String GetPath() const = 0;
		virtual const String GetProtocol() const = 0;
	};
}
