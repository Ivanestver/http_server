#pragma once
#include "core/str.h"
#include "message/export_decl.h"

namespace message
{
	class MESSAGE IHTTPRequestStartLine
	{
	public:
		virtual const String GetMethod() const = 0;
		virtual const String GetPath() const = 0;
		virtual const String GetProtocol() const = 0;
	};
}
